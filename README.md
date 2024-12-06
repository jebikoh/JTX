# JTX

This is my version of PBRT that I am writing as I go through PBRT 4th edition.

Current progress is being worked on in-parallel here:
- [JTXLib](https://github.com/jebikoh/jtxlib)
- [Ray Tracing](https://github.com/jebikoh/raytracing)
- [Cuda Ray Tracing](https://github.com/jebikoh/cudart)

If you want to push or pull updates from JTXLib, use this after you clone the repo:

`git remote add jtxlib https://github.com/jebikoh/jtxlib.git`

Then push and pull via:

```
> git subtree push --prefix=lib/jtxlib jtxlib main
> git subtree pull --prefix=lib/jtxlib jtxlib main
```
