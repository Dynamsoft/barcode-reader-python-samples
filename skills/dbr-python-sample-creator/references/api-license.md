# API Reference: dynamsoft_license

Module: `dynamsoft_license`

## Classes

### LicenseManager

All methods are **static**.

| Method | Signature | Returns |
|--------|-----------|---------|
| `init_license` | `(license: str) -> Tuple[int, str]` | (error_code, error_message). Must be called before using any DCV functionality |
| `set_device_friendly_name` | `(name: str) -> Tuple[int, str]` | (error_code, error_message) |
| `set_max_concurrent_instance_count` | `(count_for_this_device: int) -> Tuple[int, str]` | (error_code, error_message) |
| `get_device_uuid` | `(uuid_generation_method: int) -> Tuple[int, str, str]` | (error_code, error_message, uuid). Method: 1=random, 2=hardware-based |
| `set_license_cache_path` | `(directory_path: str) -> Tuple[int, str]` | (error_code, error_message). Call before `init_license` |

### LicenseModule

| Method | Signature | Returns |
|--------|-----------|---------|
| `get_version` (static) | `() -> str` | Module version string |

## Usage Pattern

```python
from dynamsoft_license import LicenseManager
error_code, error_msg = LicenseManager.init_license("YOUR-LICENSE-KEY")
if error_code != 0:
    print(f"License error: {error_msg}")
```
