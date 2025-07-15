from dynamsoft_barcode_reader_bundle import *
import os

class MyIntermediateResultReceiver(IntermediateResultReceiver):
    """
    A receiver class that records location and decoding information
    from intermediate barcode decoding results.

    Attributes:
        locations (list): Stores locations from localized barcodes.
        result_locs (list): Stores locations from decoded barcodes.
    """
    def __init__(self):
        self.locations = []
        super().__init__()
    def on_localized_barcodes_received(self, result: "LocalizedBarcodesUnit", info: IntermediateResultExtraInfo) -> None:
        if info.is_section_level_result:
            try:
                for i in range(result.get_count()):
                    element = result.get_localized_barcode(i)
                    self.locations.append(element.get_location())
            except Exception as e:
                print("on_localized_barcodes_received error:",e)

def is_within_10_percent(area1, area2):
    if area1 == 0 or area2 == 0:
        return False
    ratio = abs(area1 - area2) / max(area1, area2)
    return ratio <= 0.10

def seem_as_same_location(location: Quadrilateral, result_loc: Quadrilateral) -> bool:
    x = sum(p.x for p in location.points) / len(location.points)
    y = sum(p.y for p in location.points) / len(location.points)
    central_point = Point(int(x),int(y))
    if not result_loc.contains(central_point):
        return False
    if is_within_10_percent(location.get_area(), result_loc.get_area()):
        return True
    return False

def remove_if_loc_exists_in_result_locs(locations: List[Quadrilateral], result_locs:List[Quadrilateral]) -> Tuple[List[Quadrilateral], List[Quadrilateral]]:
    if not locations or not result_locs:
        return locations, result_locs
    ret_loc, ret_res_loc = [], []

    excluded_loc,include_res_locs = set(), set()

    for i in range(len(locations)):
        for j in range(len(result_locs)):
            if seem_as_same_location(locations[i], result_locs[j]):
                include_res_locs.add(j)
                excluded_loc.add(i)
                break

    for i in include_res_locs:
        ret_res_loc.append(result_locs[i])

    for i in range(len(locations)):
        if i not in excluded_loc:
            ret_loc.append(locations[i])
    return ret_loc, ret_res_loc

def draw_on_image(image: ImageData, locations: List[Quadrilateral], result_locs:List[Quadrilateral]) -> ImageData:
    drawer = ImageDrawer()
    loc, res_loc = remove_if_loc_exists_in_result_locs(locations, result_locs)
    if loc:
        image = drawer.draw_on_image(image, loc, 0xFFFF0000, 2)
    if res_loc:
        image = drawer.draw_on_image(image, res_loc, 0xFF00FF00, 2)
    return image

if __name__ == '__main__':
    # 1. Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
    errorCode, errorMsg = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
    if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
    else:
        # 2. Create an instance of CaptureVisionRouter.
        cvr_instance = CaptureVisionRouter()

        im = cvr_instance.get_intermediate_result_manager()
        irr = MyIntermediateResultReceiver()
        im.add_result_receiver(irr)

        # 3. Replace by your own image path.
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../images/GeneralBarcodes.png"
        io = ImageIO()

        # 4. Read image from file.
        err, image = io.read_from_file(image_path)
        if err != EnumErrorCode.EC_OK:
            print("Failed to read image:", err)
            exit()
        # 5. Decode barcodes from the image.
        result = cvr_instance.capture(image, EnumPresetTemplate.PT_READ_BARCODES)

        # 6. Check error code.
        if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Warning:", result.get_error_code(), result.get_error_string())
        elif result.get_error_code() != EnumErrorCode.EC_OK:
            print("Error:", result.get_error_code(), result.get_error_string())

        # 7. Extract the locations of decoded barcodes from the result.
        result_locs = []
        barcode_result = result.get_decoded_barcodes_result()
        if barcode_result:
            for i,item in enumerate(barcode_result.get_items()):
                result_locs.append(item.get_location())

        # 7. Draw the outline border of the barcodes on the image.
        # The barcodes that have been decode successfully are marked as green(0xFF00FF00)
        # The barcodes that only have been localized are marked as red(0xFFFF0000)
        if irr.locations or result_locs:
            image_complete = draw_on_image(image, irr.locations, result_locs)

            result_image_path = os.path.join(os.path.dirname(image_path),
                                        os.path.splitext(os.path.basename(image_path))[0] + "_result.png")

            # 8. Save the image.
            io.save_to_file(image_complete,result_image_path)
            import platform
            system = platform.system()
            if system == "Windows":
                os.startfile(result_image_path)
            elif system == "Darwin":
                os.system(f"open '{result_image_path}'")
            else:
                ret = os.system(f"xdg-open '{result_image_path}'")
                if ret != 0:
                    print("Failed to open the result image. Please check the file manually:", result_image_path)
        else:
            print("No barcode detected.")
    input("Press Enter to quit...")