#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

int main()
{
	char *line;
	int fd;

	// テスト用のファイルを開く
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return (1);
	}

	while (1)
	{
		// 1行読み込んで line に格納
		line = get_next_line(fd);
		
		// EOF（ファイルの終わり）に到達したら break
		if (!line)
			break;
		
		// 読み込んだ行を表示
		printf("%s", line);
		
		// 使い終わったメモリは必ず free する（メモリリーク防止）
		free(line);
	}
	
	close(fd);
	return (0);
}
