# channel-map

Channel mapping library between Detector and Readout FEE

## Install

```sh
cmake -S . -B .build
cmake --build .build
cmake --install .build
```

## Uninstall

```sh
xargs rm < .build/install_manifest.txt
rm -rf .build
```
