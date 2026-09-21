# ---- build stage: compile the FastCGI mini server ----
FROM debian:bookworm-slim AS builder

WORKDIR /build

COPY server/ .

RUN apt-get update && \
    apt-get install -y --no-install-recommends gcc libc6-dev make libfcgi-dev && \
    make && \
    rm -rf /var/lib/apt/lists/*

# ---- final stage: nginx + the compiled server ----
FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends nginx spawn-fcgi libfcgi0ldbl wget && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /build/server /usr/local/bin/server
COPY nginx/nginx.conf /etc/nginx/nginx.conf

RUN chmod +x /usr/local/bin/server && \
    chown www-data:www-data /usr/local/bin/server /etc/nginx/nginx.conf && \
    mkdir -p /var/lib/nginx/body /var/lib/nginx/proxy /var/lib/nginx/fastcgi \
             /var/lib/nginx/uwsgi /var/lib/nginx/scgi && \
    chown -R www-data:www-data /var/lib/nginx

USER www-data

HEALTHCHECK --interval=30s --timeout=3s --retries=3 \
    CMD wget -qO- http://127.0.0.1:81/status || exit 1

CMD ["/bin/sh", "-c", "spawn-fcgi -a 127.0.0.1 -p 8080 -- /usr/local/bin/server && exec nginx -g 'daemon off;'"]
