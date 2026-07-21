# Rudesheim-Embedded-Board-Loopback

Rudesheim layer 2: host-side test double Board implementation for unit testing.

Pulls in [Rudesheim-Embedded-Base](https://github.com/devid-rudesheim/Rudesheim-Embedded-Base)
and [Rudesheim-Embedded-Foundation](https://github.com/devid-rudesheim/Rudesheim-Embedded-Foundation)
automatically as declared dependencies.

## Install

Add it to `lib_deps` in `platformio.ini`:

```ini
[env:native]
platform = native
lib_deps =
    https://github.com/devid-rudesheim/Rudesheim-Embedded-Board-Loopback.git#v0.0.1
```

Then fetch it:

```sh
pio pkg install -e native
```

Or install directly by URL without editing `platformio.ini`:

```sh
pio pkg install -e native -l "https://github.com/devid-rudesheim/Rudesheim-Embedded-Board-Loopback.git#v0.0.1"
```

## Uninstall

```sh
pio pkg uninstall -e native -l "Rudesheim-Embedded-Board-Loopback"
```

Removes Base and Foundation along with it, as long as nothing else in the
environment still depends on them.
