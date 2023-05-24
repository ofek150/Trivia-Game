#include "IRequestHandler.h"

RequestResult IRequestHandler::ErrorResult(std::exception e) const
{
    RequestResult requestResult;
    ErrorResponse errorResponse;
    errorResponse.errorMessage = e.what();
    std::cerr << e.what() << std::endl;
    requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
    return requestResult;
}
