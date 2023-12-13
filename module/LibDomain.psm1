using namespace System.Management.Automation

$importModule = Get-Command -Name Import-Module -Module Microsoft.PowerShell.Core
&$importModule ([IO.Path]::Combine($PSScriptRoot, '..', 'bin', 'LibDomain.dll')) -ErrorAction Stop

Function Get-RootDSE {
    <#
    .SYNOPSIS
    Gets the RootDSE from LDAP server.
    #>
    $rootDSE = [LibDomain.Native]::get_root_dse()
    
    [PSCustomObject]@{
        RootDSE = $rootDSE
    }
}
