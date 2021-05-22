FROM alpine:latest

RUN apk update ; apk upgrade

RUN apk add --no-cache \
    binutils \
    libc6-compat

COPY build/ App/
WORKDIR /App
ENTRYPOINT ["/bin/sh"]