FROM alpine:latest

RUN apk update \
    && apk upgrade \
    && apk add --no-cache binutils libc6-compat

COPY build/ App/
COPY scripts/ App/

RUN chmod +x App/ex1.sh \
    && chmod +x App/ex2.sh \
    && chmod +x App/ex3.sh \
    && chmod +x App/ex4.sh 

WORKDIR /App
ENTRYPOINT ["/bin/sh"]