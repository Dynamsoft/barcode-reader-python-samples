# CaptureVisionRouter Module API Reference

Module: `dynamsoft_barcode_reader_bundle`

---

## Enums

### EnumPresetTemplate (str, Enum)

| Constant | Purpose |
|----------|---------|
| `PT_DEFAULT` | Default template |
| `PT_READ_BARCODES` | General barcode reading |
| `PT_READ_BARCODES_SPEED_FIRST` | Barcode reading optimized for speed |
| `PT_READ_BARCODES_READ_RATE_FIRST` | Barcode reading optimized for read rate |
| `PT_READ_SINGLE_BARCODE` | Read a single barcode |

### EnumCaptureState (IntEnum)

| Member | Description |
|--------|-------------|
| `CS_STARTED` | Capturing started |
| `CS_STOPPED` | Capturing stopped |
| `CS_PAUSED` | Capturing paused |
| `CS_RESUMED` | Capturing resumed |

### EnumImageSourceState (IntEnum)

| Member | Description |
|--------|-------------|
| `ISS_BUFFER_EMPTY` | Image source buffer is empty |
| `ISS_EXHAUSTED` | Image source is exhausted |

---

## Classes

### CaptureVisionRouter

The main entry point for image processing. Handles single-image capture and continuous capture from an image source.

**Constructor:** `CaptureVisionRouter()`

#### Single-Image Capture

| Method | Signature | Description |
|--------|-----------|-------------|
| `capture` | `(*args) -> CapturedResult` | Process a single image. Args: `(file_path, [template_name])` or `(file_bytes, [template_name])` or `(ImageData, [template_name])` or `(numpy.ndarray, [EnumImagePixelFormat], [template_name])` |
| `capture_multi_pages` | `(file: Union[str, bytes], template_name: str = "") -> CapturedResultArray` | Process a multi-page image file (e.g. PDF/TIFF) |

#### Settings Management

| Method | Signature | Description |
|--------|-----------|-------------|
| `init_settings` | `(content: str) -> Tuple[int, str]` | Load template from a JSON string |
| `init_settings_from_file` | `(file_path: str) -> Tuple[int, str]` | Load template from a JSON file |
| `output_settings` | `(template_name: str, include_default_values: bool = False) -> Tuple[int, str, str]` | Export template to JSON string. Use `"*"` for all templates |
| `output_settings_to_file` | `(template_name: str, file_path: str, include_default_values: bool = False) -> Tuple[int, str]` | Export template to JSON file |
| `get_simplified_settings` | `(template_name: str) -> Tuple[int, str, SimplifiedCaptureVisionSettings]` | Get simplified settings for a template |
| `update_settings` | `(template_name: str, settings: SimplifiedCaptureVisionSettings) -> Tuple[int, str]` | Update template with simplified settings |
| `reset_settings` | `() -> Tuple[int, str]` | Reset all templates to factory defaults |
| `get_parameter_template_count` | `() -> int` | Get count of loaded templates |
| `get_parameter_template_name` | `(index: int) -> Tuple[int, str]` | Get template name by index |

#### Continuous Capture (Video/Streaming)

| Method | Signature | Description |
|--------|-----------|-------------|
| `set_input` | `(adapter: ImageSourceAdapter) -> Tuple[int, str]` | Set image source for continuous capture |
| `get_input` | `() -> ImageSourceAdapter` | Get the attached image source adapter |
| `start_capturing` | `(template_name: str = "", wait_for_thread_exit: bool = False) -> Tuple[int, str]` | Start continuous processing |
| `stop_capturing` | `(wait_for_remaining_tasks: bool = True, wait_for_thread_exit: bool = True) -> None` | Stop continuous processing |
| `pause_capturing` | `() -> None` | Pause capture (blocks current thread) |
| `resume_capturing` | `() -> None` | Resume capture |
| `switch_capturing_template` | `(template_name: str) -> Tuple[int, str]` | Switch template during capture |

#### Listeners & Receivers

| Method | Signature | Description |
|--------|-----------|-------------|
| `add_result_receiver` | `(receiver: CapturedResultReceiver) -> Tuple[int, str]` | Add captured result callback receiver |
| `remove_result_receiver` | `(receiver: CapturedResultReceiver) -> Tuple[int, str]` | Remove result receiver |
| `add_result_filter` | `(filter: CapturedResultFilter) -> Tuple[int, str]` | Add result filter |
| `remove_result_filter` | `(filter: CapturedResultFilter) -> Tuple[int, str]` | Remove result filter |
| `add_capture_state_listener` | `(listener: CaptureStateListener) -> Tuple[int, str]` | Listen for capture state changes |
| `remove_capture_state_listener` | `(listener: CaptureStateListener) -> Tuple[int, str]` | Remove capture state listener |
| `add_image_source_state_listener` | `(listener: ImageSourceStateListener) -> Tuple[int, str]` | Listen for image source state changes |
| `remove_image_source_state_listener` | `(listener: ImageSourceStateListener) -> Tuple[int, str]` | Remove image source state listener |

#### Other

| Method | Signature | Description |
|--------|-----------|-------------|
| `get_buffered_items_manager` | `() -> BufferedItemsManager` | Get the buffered items manager |
| `get_intermediate_result_manager` | `() -> IntermediateResultManager` | Get the intermediate result manager |

#### Static Methods

| Method | Signature | Description |
|--------|-----------|-------------|
| `append_model_buffer` | `(model_name: str, model_buffer: bytes, max_model_instances: int) -> Tuple[int, str]` | Load a model into memory |
| `append_dl_model_buffer` | `(model_name: str, model_buffer: bytes, max_model_instances: int) -> Tuple[int, str]` | Load a deep learning model into memory |
| `clear_dl_model_buffers` | `() -> None` | Free all DL models from memory |
| `set_global_intra_op_num_threads` | `(intra_op_num_threads: int) -> None` | Set threads for model execution (0-256) |

---

### SimplifiedCaptureVisionSettings

Simplified settings object used with `get_simplified_settings` / `update_settings`.

| Attribute | Type | Description |
|-----------|------|-------------|
| `roi` | `Quadrilateral` | Region of interest |
| `roi_measured_in_percentage` | `int` | Whether ROI is in percentage (1) or pixels (0) |
| `max_parallel_tasks` | `int` | Max parallel processing tasks |
| `timeout` | `int` | Max time in ms for capture |
| `min_image_capture_interval` | `int` | Min interval in ms between captures |
| `output_original_image` | `int` | Whether to output original image |
| `barcode_settings` | `SimplifiedBarcodeReaderSettings` | Barcode reader settings |

---

### CapturedResult (extends CapturedResultBase)

Result of a capture operation on a single image. Contains result items of various types.

| Method | Signature | Description |
|--------|-----------|-------------|
| `get_items` | `() -> List[CapturedResultItem]` | Get all captured result items |
| `get_decoded_barcodes_result` | `() -> DecodedBarcodesResult` | Get barcode results |
| `__getitem__` | `(index: int) -> CapturedResultItem` | Index access to items |

*Inherited from CapturedResultBase:* `get_original_image_hash_id()`, `get_original_image_tag()`, `get_rotation_transform_matrix()`, `get_error_code()`, `get_error_string()`

### CapturedResultArray

Container for multi-page capture results.

| Method | Signature | Description |
|--------|-----------|-------------|
| `get_results` | `() -> List[CapturedResult]` | Get all CapturedResult objects |

---

### CapturedResultReceiver

Subclass this to receive results during continuous capture. Override the callback methods you need.

| Callback | Signature | Trigger |
|----------|-----------|---------|
| `on_captured_result_received` | `(result: CapturedResult) -> None` | After each image is processed (all results) |
| `on_original_image_result_received` | `(result: OriginalImageResultItem) -> None` | When original image is available (requires `OutputOriginalImage=1`) |
| `on_decoded_barcodes_received` | `(result: DecodedBarcodesResult) -> None` | When barcodes are decoded |

Utility: `get_name() -> str`, `set_name(name: str) -> None`

---

### CapturedResultFilter

Subclass this to filter results. Same callback signatures as `CapturedResultReceiver`.

Utility: `get_name() -> str`, `set_name(name: str) -> None`

---

### CaptureStateListener (ABC)

Abstract listener for capture state changes. Must implement:

- `on_capture_state_changed(state: int) -> None` -- `state` is an `EnumCaptureState` value

### ImageSourceStateListener (ABC)

Abstract listener for image source state changes. Must implement:

- `on_image_source_state_received(state: int) -> None` -- `state` is an `EnumImageSourceState` value

---

### BufferedItemsManager

Manages buffered items during continuous capture.

| Method | Signature | Description |
|--------|-----------|-------------|
| `set_max_buffered_items_count` | `(count: int) -> None` | Set max buffered items |
| `get_max_buffered_items_count` | `() -> int` | Get max buffered items |
| `get_buffered_character_item_set` | `() -> BufferedCharacterItemSet` | Get buffered character items |

---

### IntermediateResultManager

Manages intermediate result receivers.

| Method | Signature | Description |
|--------|-----------|-------------|
| `add_result_receiver` | `(receiver: IntermediateResultReceiver) -> int` | Add intermediate result receiver |
| `remove_result_receiver` | `(receiver: IntermediateResultReceiver) -> int` | Remove intermediate result receiver |
| `get_original_image` | `(image_hash_id: str) -> ImageData` | Get original image by hash ID |

---

### IntermediateResultReceiver

Subclass to receive intermediate processing results. All callbacks have signature `(result: <UnitType>, info: IntermediateResultExtraInfo) -> None`.

**Key callbacks:** `on_task_results_received`, `on_predetected_regions_received`, `on_localized_barcodes_received`, `on_decoded_barcodes_received`, `on_binary_image_unit_received`, `on_grayscale_image_unit_received`, `on_unit_result_received`

Utility: `get_observation_parameters() -> ObservationParameters`

---

### CaptureVisionRouterModule

| Method | Signature | Description |
|--------|-----------|-------------|
| `get_version` (static) | `() -> str` | Get module version string |
