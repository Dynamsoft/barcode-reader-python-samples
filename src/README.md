### How to Build
Download [Dynamsoft Barcode Reader SDK v7.2.2](https://github.com/dynamsoft-dbr/python-barcode/releases/tag/v7.2.2) for Raspberry Pi.

Copy **libDynamsoftBarcodeReader.so** to `/usr/lib`. If you don't have access to `/usr/lib`, try to copy the library to `/usr/local/lib` and set the **LD_LIBRARY_PATH** as follows:

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

Build and install the Python extension:

```
cd src
sudo python setup.py build install
```

