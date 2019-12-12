Language bindings for Raspberry Pi
==================================
TM1637Controller for Raspberry Pi. This feature is *experimental* and unstable currently.

# How to build
## C#
```
# generate shared library (.so) and C# library (.dll)
make binding-csharp

cd csharp/examples/SomeExampleDirectory

# run example project
dotnet run
```

# Requirements
- Wiring PI (`libwiringPi.so`)
- SWIG (3.0.12 or over)
- .NET Runtime and SDK
  - [.NET Core SDK](https://dotnet.microsoft.com/download/dotnet-core) (2.2 or over)
  - or [Mono](https://github.com/mono/mono) + [MSBuild](https://github.com/mono/msbuild)