# JTX

This is my long term offline phyiscally-based ray tracer (building it as I go through Physically Based Rendering, 4th edition)

Current progress is being written in these repositories:
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