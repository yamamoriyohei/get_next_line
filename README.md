*This project has been created as part of the 42 curriculum by yyamamor.*

# Get Next Line

## Description
このプロジェクトは、ファイルディスクリプタからテキストを読み込み、1行ずつ返す関数を作成するものです。主な目的は、C言語における静的変数（Static Variables）の仕組み、動的メモリの割り当て、および低レベルでのファイル入出力（I/O）操作を学ぶことです。ループの中で `get_next_line` を呼び出すことで、ファイルの終端（EOF）に到達するまでテキスト全体を1行ずつ読み進めることができます。

## Instructions
**コンパイル方法:**
`get_next_line` 関数を使用するには、ソースファイルを独自の `main.c` と一緒にコンパイルします。コンパイル時に `-D` オプションを使って `BUFFER_SIZE`（一度に読み込むバイト数）を指定することができます。

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

**実行方法:**
コンパイル後、生成された実行ファイルを実行します。
```bash
./a.out
```

## Algorithm and Data Structure
**データ構造:**
このプロジェクトで使用されている主なデータ構造は、標準的なC言語の文字列（`char *`）です。関数が複数回呼び出されても読みかけのデータを失わずに状態を保持するため、単一の `static char *save` ポインタを使用しています。プロジェクトの規定により標準ライブラリの関数使用が厳しく制限されているため、文字列の結合や検索を安全に行う独自のユーティリティ関数（`ft_strjoin`, `ft_strlen`, `ft_strchr`）を実装しました。

**アルゴリズム:**
効率的な読み込みと厳密なメモリ管理を実現するため、以下の3ステップのアルゴリズムを採用しています。
1. **読み込みと保存 (Read to Save)**: `BUFFER_SIZE` 分のバッファを用意し、ファイルディスクリプタからデータを読み込みます。読み込んだデータは、メモリリークを考慮した自作の `ft_strjoin` を用いて静的変数 `save` に結合されます。これを改行文字（`\n`）が現れるか、EOFに到達するまで繰り返します。
2. **行の抽出 (Extract Line)**: 改行またはEOFが見つかると、現在の1行分の長さを計算し、その行のためだけに新しくメモリを割り当てて `save` から文字列を抽出して返します。
3. **残りの保存 (Clean Save)**: 抽出後、`save` を更新して改行以降の「残りの文字列」だけを保持するようにします。ファイルを最後まで読み切った場合は、メモリリークを防ぐために `save` を適切に `free` して `NULL` に戻します。

## Resources
- [Linux Programmer's Manual - read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [C Programming: Static Variables](https://en.wikipedia.org/wiki/Static_variable)
- **AIの使用について:** 開発過程において、AI (LLM) を使用しました。具体的には、42の厳格なコーディング規約「Norminette v3（特に関数の25行制限）」に準拠するためのコード構造のリファクタリング、`malloc` 失敗時のエッジケースにおけるメモリリークの特定と解消、および本 README の構造化に利用しています。
