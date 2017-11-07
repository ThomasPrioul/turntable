namespace ThomasPrioul.Extensions
{
    static class IStringLocalizerExtensions
    {
        #region Methods

        public static string Format(this Microsoft.Extensions.Localization.LocalizedString localizedString, params object[] args)
        {
            return string.Format(localizedString, args);
        }

        #endregion Methods
    }
}