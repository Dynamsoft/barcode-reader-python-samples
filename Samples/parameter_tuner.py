import time
import os
import dynamsoft_barcode_reader_bundle
from dynamsoft_barcode_reader_bundle import *

class LoopInfo():
    def __init__(self,cvr_instance : CaptureVisionRouter, image_path: str = None,matched_template: str = None, description: str = None, template_path: str = None):
        self.cvr_instance = cvr_instance
        self.image_path = image_path
        self.template_path = template_path
        self.matched_template = matched_template
        self.description = description

sample_images = {
    "1": ("images/blurry.png", "ReadBlurryBarcode.json", "Suitable for blurred barcode"),
    "2": ("images/GeneralBarcodes.png", "ReadMultipleBarcode.json", "Suitable for multiple barcodes"),
    "3": ("images/inverted-barcode.png", "ReadInvertedBarcode.json", "Suitable for colour inverted barcode"),
    "4": ("images/DPM.png", "ReadDPM.json", "Suitable for Direct Part Marking barcode"),
}

def select_image():
    print("Available Sample Scenarios:")
    print("[1] Blurry barcode")
    print("[2] Multiple barcodes")
    print("[3] Colour Inverted Barcode")
    print("[4] Direct Part Marking (DPM)")
    print("[5] Custom Image")

    while True:
        choice = input("\nEnter the number of the image to test, or provide a full path to your own image:\n> ").strip(' \'"')
        image_path, matched_template, description = None, None, None
        if choice in sample_images:
            image_path, matched_template, description = sample_images[choice]
            image_path = os.path.join("..", image_path)
        elif choice == "5":
            image_path = input("Enter full path to your custom image:\n> ").strip(' \'"')
            if not os.path.isfile(image_path):
                print("Invalid path input, please try again.")
                continue
        else:
            image_path = choice
            if not os.path.isfile(image_path):
                print("Invalid path input, please try again.")
                continue
        image_path = os.path.abspath(image_path)
        return image_path, matched_template, description

def select_template(matched_template, description):
    print("\nSelect template for this image:")

    options = []

    if matched_template:
        options.append((matched_template, description))
    options.append(("ReadBarcodes_Default.json", "General purpose settings"))
    options.append(("Custom template", "Use your own template"))

    for idx, (path, desc) in enumerate(options, start=1):
            print(f"[{idx}] {path} ({desc})")

    print("\nEnter the number of the template to test, or provide a full path to your own template:")

    while True:
        choice = input("> ").strip(' \'"')
        selected_path = None
        if choice.isdigit():
            index = int(choice) - 1
            if 0 <= index < len(options):
                selected_path = options[index][0]
                if selected_path == options[-1][0]:
                    selected_path = input("Enter full path to your custom template:\n> ").strip(' \'"')
                elif selected_path == options[-2][0]:
                    package_dir = os.path.dirname(dynamsoft_barcode_reader_bundle.__file__)
                    selected_path = os.path.join(package_dir, "Templates", "DBR-PresetTemplates.json")
                else:
                    selected_path = os.path.join("..", "CustomTemplates", selected_path)
            else:
                print("Invalid choice, please try again.")
                continue
        else:
            selected_path = choice
        if selected_path:
            selected_path = os.path.abspath(selected_path)
            if not os.path.isfile(selected_path):
                print("Invalid template path, please try again.")
                continue
            return selected_path
        else:
            print("Invalid input, please try again.")

def run(cvr_instance:CaptureVisionRouter, image_path:str, template_path:str):
    print("\nRunning with:")
    print(f"Image: {image_path}")
    print(f"Template: {template_path}")
    start_time = time.time()
    result_array = cvr_instance.capture_multi_pages(image_path,"")
    elapsed_ms = int((time.time() - start_time) * 1000)
    results = result_array.get_results()
    if results is None or len(results) == 0:
        print("No results.")
    else:
        for i, result in enumerate(results):
            print(f"\nResult{' ' + str(i+1) if i > 0 else ''}:")
            error_code = result.get_error_code()
            if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                print(f"Error: {error_code}, {result.get_error_string()}")
            barcode_result = result.get_decoded_barcodes_result()
            if barcode_result:
                items = barcode_result.get_items()
                for j, item in enumerate(items):
                    if isinstance(item, BarcodeResultItem):
                        print(f"Barcode result [{i+1}-{j+1}]: {item.get_text()} (Format: {item.get_format_string()})")
    print(f"Time used: {elapsed_ms} ms...\n")

def loop_inner(loop_info : LoopInfo, get_image: bool = True, get_template: bool = True):
    if get_image:
        loop_info.image_path, loop_info.matched_template, loop_info.description = select_image()
    if get_template:
        loop_info.template_path = select_template(loop_info.matched_template, loop_info.description)
        error_code, error_string = loop_info.cvr_instance.init_settings_from_file(loop_info.template_path)
        if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Init template failed:", error_code, error_string)
            return

    run(loop_info.cvr_instance, loop_info.image_path, loop_info.template_path)

def main():

    print("Welcome to ParameterTuner!\n")

    # Initialize license.
    # The string "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9" here is a free public trial license. Note that network connection is required for this license to work.
    # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    error_code, error_string = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
    if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", str(error_code) + ", ErrorString:", error_string)

    loop_info = LoopInfo(CaptureVisionRouter())
    loop_inner(loop_info)

    while True:
        print("What would you like to do next?")
        print("[1] Try a different template")
        print("[2] Load another image")
        print("[3] Exit")
        choice = input("Enter your choice:\n> ").strip()
        if choice == "1":
            loop_inner(loop_info, get_image=False, get_template=True)
        elif choice == "2":
            loop_inner(loop_info, get_image=True, get_template=False)
        elif choice == "3":
            print("Thank you for using ParameterTuner!")
            break
        else:
            print("Invalid input. Returning to main menu.")

if __name__ == "__main__":
    main()
