#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <stdio.h>

static char *ngx_http_ysoftman(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_ysoftman_handler(ngx_http_request_t *r);

// nginx.conf directives(명령) 으로 사용할 값 지정
static ngx_command_t ngx_http_ysoftman_commands[] = {
    {ngx_string("ysoftman_test_module"),  // directive 로 사용할 값
     NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS, // location로 사용하고 인자는 받지 않는다.
     ngx_http_ysoftman,                   // 셋업(entry point)함수 지정
     0,
     0,
     NULL},
    ngx_null_command // command 끝
};

// context 구조
static ngx_http_module_t ngx_http_ysoftman_ctx = {
    NULL, // preconfiguration
    NULL, // postconfiguration
    NULL, // create main configuration
    NULL, // init main configuration
    NULL, // create server configuration
    NULL, // merge server configuration
    NULL, // create location configuration
    NULL  // merge location configuration
};

// 모듈 정의
ngx_module_t ngx_http_ysoftman_module = {
    NGX_MODULE_V1,
    &ngx_http_ysoftman_ctx,     // 모듈 컨텍스트 지정
    ngx_http_ysoftman_commands, // 모듈 directives 설정
    NGX_HTTP_MODULE,            // 모듈 타입
    NULL,                       // master 초기화 함수
    NULL,                       // module 초기화 함수
    NULL,                       // process 초기화 함수
    NULL,                       // thread 초기화 함수
    NULL,                       // thread 종료 함수
    NULL,                       // process 종료 함수
    NULL,                       // master 종료 함수
    NGX_MODULE_V1_PADDING};

// 모듈 셋업(entry point) 함수
static char *ngx_http_ysoftman(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf;

    // core 모듈의 location 설정 가져오기
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    // ysoftman 핸들 함수 등록
    clcf->handler = ngx_http_ysoftman_handler;

    return NGX_CONF_OK;
}

// ysoftman 핸들러
static ngx_int_t ngx_http_ysoftman_handler(ngx_http_request_t *r)
{
    u_char resp_msg[] = "ysoftman c module response!";

    // 요청 내용 보기
    fprintf(stderr, "r->uri: %s", r->uri.data);
    fprintf(stderr, "r->args: %s", r->args.data);
    // r->header_in 에 요청 헤더내용이 들어 있다.

    // 응답 헤더 설정
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *)"text/plain";
    r->headers_out.content_length_n = sizeof(resp_msg) - 1;
    r->headers_out.status = NGX_HTTP_OK;
    // 응답 헤더 전송
    ngx_http_send_header(r);

    // 응답 바디(본문) 설정
    ngx_buf_t *body_buffer = NULL;
    ngx_chain_t out_chain;

    // r->pool 로 부터 버퍼 할당을 받는다.
    body_buffer = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if (body_buffer == NULL)
    {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "fail to ngx_pcalloc");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    // 응답 버퍼에 데이터 시작과 끝 설정
    body_buffer->pos = resp_msg;
    body_buffer->last = resp_msg + sizeof(resp_msg) - 1;
    // 응답 버퍼 는 read-only 메모리로 설정
    body_buffer->memory = 1;
    // 마지막 버퍼임을 표시(요청에 처리에 더이상의 버퍼는 사용하지 않는다.)
    body_buffer->last_buf = 1;

    // 응답 버퍼를 체인에 연결
    out_chain.buf = body_buffer;
    out_chain.next = NULL;

    // 응답 본문이 설정된 체인을 필터로 보내면 필터 처리 후 전송된다.
    return ngx_http_output_filter(r, &out_chain);
}
