using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Threading;
using Microsoft.AspNetCore;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Hosting.Server.Features;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.CommandLineUtils;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Localization;
using Microsoft.Extensions.Logging;
using ThomasPrioul.Extensions;
using static System.Environment;

namespace Turntable
{
    class Program
    {
        static int Main(string[] args)
        {
            var app = new CommandLineApplication
            {
                Description = "Turntable background service - C# version" + NewLine + "Thomas Prioul - 2017",
                FullName = "Turntable.net - C# version",
                Name = "Turntable.net",
            };
            app.HelpOption("-h|--help|-?");
            app.VersionOption("-v|--version", "1.0");

            var ipOption = app.Option("--ip", "The IP address (and therefore the interface) to use", CommandOptionType.SingleValue);
            var portOption = app.Option("--port", "The port to use for TCP communication", CommandOptionType.SingleValue);
            var stepsOption = app.Option("--steps", "The number of steps for the motor", CommandOptionType.SingleValue);
            var reverseOption = app.Option("--reverse", "Invert the motor's direction", CommandOptionType.NoValue);
            var polarityOption = app.Option("--polaritySwitch", "Invert the polarity at the specified position in steps", CommandOptionType.SingleValue);

            app.OnExecute(async () =>
            {
                using (var host = CreateWebApp(args))
                {
                    var services = host.Services;
                    var log = services.GetService<ILoggerFactory>().CreateLogger<Program>();
                    var strings = services.GetService<IStringLocalizer<Program>>();
                    var hostEnv = services.GetService<IHostingEnvironment>();

                    log.LogInformation(strings["Hosting environment: {0}{1}Content root path: \"{2}\""]
                        .Format(hostEnv.EnvironmentName, NewLine, hostEnv.ContentRootPath));

                    Action shuttingDownMessage = () => log.LogInformation(strings["Application is shutting down..."]);
                    using (var cancel = new CancellableApplication(shuttingDownMessage))
                    {
                        await host.StartAsync(cancel.Token);

                        if (host.ServerFeatures.Get<IServerAddressesFeature>()?.Addresses is ICollection<string> serverAddresses)
                            log.LogInformation(strings["Now listening on:{0}{1}"]
                                .Format(NewLine, string.Join(NewLine, serverAddresses)));

                        using (var turntableService = services.GetService<TurntableService>())
                        {
                            await host.WaitForShutdownAsync(cancel.Token);
                        }
                    }
                }

                return 0;
            });

            try
            {
                return app.Execute(args);
            }
            catch (Exception error)
            {
                Console.WriteLine(error);
                return -1;
            }
        }

        static IWebHost CreateWebApp(string[] args)
        {
            const ushort defaultPort = 2017;
            var cfg = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddInMemoryCollection(new Dictionary<string, string>()
                {
                    ["ip"] = IPAddress.Any.ToString(),
                    ["port"] = defaultPort.ToString()
                })
                .AddEnvironmentVariables()
                .AddCommandLine(args)
                .Build();

            return new WebHostBuilder().Configure(webApp =>
            {
                webApp.UseSignalR(routes =>
                {
                });

                webApp.Run(async context =>
                {
                    await context.Response.WriteAsync("Hello World!");
                });
            })
            .ConfigureLogging(logging =>
            {
                logging.AddConsole()
                    .AddDebug()
                    .SetMinimumLevel(LogLevel.Information);
            })
            .ConfigureServices((context, services) =>
            {
                var config = context.Configuration;
                services
                    .AddLocalization()
                    .Configure<Configuration>(config)
                    .AddSingleton<TurntableService>()
                    .AddSignalR();
            })
            .UseConfiguration(cfg)
            .UseKestrel(options =>
            {
                if (!IPAddress.TryParse(cfg.GetValue("ip", ""), out var ip))
                    ip = IPAddress.Any;

                if (!ushort.TryParse(cfg.GetValue("port", ""), out var port))
                    port = defaultPort;

                options.Listen(ip, port);
            })
            .Build();
        }
    }
}
