using System;
using System.Threading;

namespace ThomasPrioul.Extensions
{
    class CancellableApplication : IDisposable
    {
        readonly CancellationTokenSource _cts;

        ManualResetEventSlim _doneEvent;

        readonly object _lock = new object();

        readonly Action _shutdownMessageCallback;   

        public CancellationToken Token => _cts.Token;

        public CancellableApplication(Action shutdownMessageCallback = null)
        {
            _cts = new CancellationTokenSource();
            _doneEvent = new ManualResetEventSlim(false);
            _shutdownMessageCallback = shutdownMessageCallback;

            void Shutdown()
            {
                if (!_cts.IsCancellationRequested)
                {
                    _shutdownMessageCallback?.Invoke();

                    try
                    {
                        _cts.Cancel();
                    }
                    catch (ObjectDisposedException)
                    {
                    }
                    catch (AggregateException)
                    {
                    }
                }

                // Wait on the given reset event
                lock (_lock)
                {
                    if (_doneEvent != null)
                    {
                        _doneEvent.Wait();
                        _doneEvent.Dispose();
                        _doneEvent = null;
                    }
                }
            };

            SetConsoleCtrlHandler((sig) =>
            {
                //Environment.ExitCode = -3;
                Shutdown();
                return true;
            }, true);

            AppDomain.CurrentDomain.ProcessExit += (sender, eventArgs) =>
            {
                //Environment.ExitCode = -1;
                Shutdown();
            };

            Console.CancelKeyPress += (sender, eventArgs) =>
            {
                // Don't terminate the process immediately, wait for the Main thread to exit gracefully.
                //Environment.ExitCode = -2;
                Shutdown();
                eventArgs.Cancel = true;
            };
        }

        #region Methods

        [System.Runtime.InteropServices.DllImport("kernel32")]
        static extern bool SetConsoleCtrlHandler(EventHandler handler, bool add);

        #endregion Methods

        #region Delegates

        delegate bool EventHandler(CtrlType sig);

        #endregion Delegates

        #region Enums

        enum CtrlType
        {
            CTRL_C_EVENT = 0,
            CTRL_BREAK_EVENT = 1,
            CTRL_CLOSE_EVENT = 2,
            CTRL_LOGOFF_EVENT = 5,
            CTRL_SHUTDOWN_EVENT = 6
        }

        #region IDisposable Support
        bool disposedValue = false;

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    try
                    {
                        _doneEvent.Set();
                        _cts.Dispose();
                        //_doneEvent.Dispose();
                    }
                    catch
                    {
                    }
                }

                disposedValue = true;
            }
        }

        public void Dispose()
        {
            Dispose(true);
        }
        #endregion

        #endregion Enums
    }
}