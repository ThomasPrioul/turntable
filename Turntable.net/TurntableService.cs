using System;
using System.Threading;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;

namespace Turntable
{
    class TurntableService : IDisposable
    {
        readonly Configuration _config;
        
        readonly ILogger<TurntableService> _log;

        //CancellationTokenSource _cts;

        public TurntableService(ILogger<TurntableService> logger, IOptions<Configuration> configuration)
        {
            _log = logger ?? throw new System.ArgumentNullException(nameof(logger));
            _config = configuration?.Value ?? throw new System.ArgumentNullException(nameof(configuration));

            _log.LogInformation($@"Configuration:
    steps: {_config.Steps}
    reverse: {_config.Reverse}
    switch polarity at: {_config.PolaritySwitch} steps");
        }

        #region IDisposable Support
        bool disposedValue = false;

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    _log.LogInformation("Dispose");
                }

                disposedValue = true;
            }
        }

        public void Dispose()
        {
            Dispose(true);
        }
        #endregion
    }
}