from dynamsoft_barcode_reader_bundle import *
from flask import Flask, request, jsonify
from typing import List, Tuple
import base64
app = Flask(__name__)

def decode_barcode_inner(data) -> Tuple[int, str, List[str]]:
    cvr_instance = CaptureVisionRouter()
    ret = []
    error_code = None
    error_string = None
    result = cvr_instance.capture(data,EnumPresetTemplate.PT_READ_BARCODES)
    if result.get_error_code() != EnumErrorCode.EC_OK and result.get_error_code() != EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
        print("Error:", result.get_error_code(), result.get_error_string())
        error_code = result.get_error_code()
        error_string = result.get_error_string()
    else:
        error_code = EnumErrorCode.EC_OK
        error_string = "Successful."
    barcode_result = result.get_decoded_barcodes_result()
    if barcode_result is None or barcode_result.get_items() == 0:
        print("No barcode detected.")
    else:
        items = barcode_result.get_items()
        print("Decoded", len(items), "barcodes.")
        for item in items:
            ret.append(item.get_text())
    return error_code, error_string, ret

@app.route('/decode_barcode', methods=['POST'])
def decode_barcode():
    """
    Barcode decoding endpoint: Accepts barcode data and returns the decoded results.

    Request Method:
        POST

    Request Headers:
        - Content-Type: Can be one of the following:
            1. multipart/form-data
            2. application/json
            3. Other binary content types

    Request Body:
        - If Content-Type is multipart/form-data:
            Include a file field named 'file' containing the barcode image file.
        - If Content-Type is application/json:
            JSON format with a 'data' field containing the Base64-encoded barcode data.
        - If Content-Type is other:
            The request body should directly contain the binary barcode data.

    Response:
        - On success: Returns a JSON array of decoded barcodes.
        - On failure: Returns error code and error message with an appropriate HTTP status code.

    Examples:
        1. Using multipart/form-data to upload a file:
            curl -X POST -F "file=@barcode.png" http://<server_ip>:8000/decode_barcode
        2. Using application/json to send Base64 data:
            curl -X POST -H "Content-Type: application/json" -d '{"data": "base64_encoded_data"}' http://<server_ip>:8000/decode_barcode
        3. Sending binary data directly:
            curl -X POST --data-binary @barcode.png http://<server_ip>:8000/decode_barcode
    """
    try:
        # get data
        content_type = request.content_type
        data = None
        if content_type.startswith('multipart/form-data'):
            if 'file' in request.files:
                file = request.files['file']
                data = file.read()
            else:
                return "No file found in multipart data", 400

        elif content_type == 'application/json':
            json_data = request.get_json(silent=True)
            if json_data:
                data = json_data.get('data')
                if data is None:
                    return "No 'data' key found in JSON", 400
                data = base64.b64decode(data)
            else:
                return "Invalid JSON", 400

        else:
            data = request.get_data()

        # Decode the barcode
        error_code, error_string, barcodes = decode_barcode_inner(data)
        if error_code != EnumErrorCode.EC_OK:
            return jsonify({
                'error_string': error_string,
                'error_code': error_code
                }), 400
        return jsonify(barcodes), 200
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':

    # Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
    error_code, error_string = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
    if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", error_code, ", ErrorString:", error_string)
    else:
        app.run(host='0.0.0.0', port=8000)