@{
    ModuleVersion = '1.0.0'
    RootModule = 'LibDomain'
    GUID = '5b502ae6-c6a7-4a22-ad26-1d9cbe164fc2'
    Author = 'august@basealt.ru'
    Copyright = 'Copyright (c) BaseALT Ltd.'
    Description = "Module to show integration between libdomain and powershell."
    PowerShellVersion = '7.0'
    CompatiblePSEditions = 'Core'
    FunctionsToExport = @(
        'Get-RootDSE'
    )
    PrivateData = @{
        PSData = @{
            Tags = @(
                'PSEdition_Core',
                'Linux'
            )
            LicenseUri = 'https://github.com/libdomain/libdomain-powershell-sample/blob/master/LICENSE.md'
            ProjectUri = 'https://github.com/libdomain/libdomain-powershell-sample'
            ReleaseNotes = 'See https://github.com/libdomain/libdomain-powershell-sample/blob/master/CHANGELOG.md'
            Prerelease = 'dev'
        }
    }
}
