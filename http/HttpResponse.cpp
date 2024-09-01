#include "HttpResponse.h"
#include <strings.h>
#include <cstdio>

HttpResponse::HttpResponse() {
    m_statusCode = StatusCode::Unknown;
    m_headers.clear();
    m_fileName = std::string();
    sendDataFunc = nullptr;
}

HttpResponse::~HttpResponse() {
}

void HttpResponse::addHeader(const std::string key, const std::string value) {
    if (key.empty() || value.empty()) {
        return;
    }
    m_headers.insert(make_pair(key, value));
}

void HttpResponse::prepareMsg(Buffer *sendBuf, int socket) {
    // 状态行
    char tmp[1024] = {0};
    int code = static_cast<int>(m_statusCode);
    sprintf(tmp, "HTTP/1.1 %d %s\r\n", code, m_info.at(code).data());
    sendBuf->appendString(tmp);
    // 响应头
    for (auto & m_header : m_headers) {
        sprintf(tmp, "%s: %s\r\n", m_header.first.data(), m_header.second.data());
        sendBuf->appendString(tmp);
    }
    // 空行
    sendBuf->appendString("\r\n");
#ifndef MSG_SEND_AUTO
    sendBuf->sendData(socket);
#endif

    // 回复的数据
    sendDataFunc(m_fileName, sendBuf, socket);
}
