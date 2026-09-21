#include <fcgi_stdio.h>
#include <stdlib.h>

int main(void)
{
    while (FCGI_Accept() >= 0)
    {
        printf("Content-Type: text/html; charset=utf-8\r\n");
        printf("\r\n");
        printf("<html>\r\n");
        printf("<head><title>Hello, World!</title></head>\r\n");
        printf("<body><h1>Hello, World!</h1></body>\r\n");
        printf("</html>\r\n");
    }

    return 0;
}
