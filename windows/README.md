## Building in Windows
- download the repository
- open *AoC.sln* solution file in Microsoft Visual Studio Community 2022
- choose solution platform and configuration and... just build it!
- binaries will be placed in *bin* directory, enjoy

## Building in Windows with CUDA
- download the repository
- make sure you've downloaded and installed *CUDA Toolkit 11.5*
- open *AoC_with_CUDA.sln* solution file in Microsoft Visual Studio Community 2022
- choose solution configuration and... just build it!
- binaries will be placed in *bin* directory, enjoy

Note: If you want to use a different version of CUDA Toolkit, change manually *CUDA 11.5.props* and *CUDA 11.5.targets* setting in *2015_with_CUDA.vcxproj* file to match the version of CUDA Toolkit installed.
