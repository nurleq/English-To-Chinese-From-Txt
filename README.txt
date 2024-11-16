Required Tools:
windows: curl (powershell etc)
gcc or clang - c compiler (mingw or llvm windows32 or windows64 builds/releases should work)
grep - gnu-windows build release should work

Linux:
You wil need `curl` and `grep` installed on your system:
--bash
sudo apt-get update
sudo apt-get install curl grep

compilation
--win cmd or bash etc
gcc -o translate translate.c
./translate

Create an English text file (e.g., `input.txt`) with each word followed by a newline:

   hello world this is a test


Run the program and provide the paths to your input and output files:
   ./translate
   Enter the path to the input English file: input.txt
   Enter the path to the output Chinese file: output.txt

The program will read `input.txt`, translate each word using `curl` and `grep`, and write the translated text to `output.txt`.

NOTES:
- Replace `"YOUR_API_KEY"` with your actual Google Translate API key.
- This example uses `curl` and `grep` for translation, which may not be the most efficient or reliable method for translating words. For better results, consider using a dedicated translation library like `libgoogle_translate` or
`papago-translate`.
- Ensure you have the necessary permissions to read from and write to files on your system.