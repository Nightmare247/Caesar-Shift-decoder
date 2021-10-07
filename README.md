# caesar-shift-decoder
Decodes caesar shift based on which key has the most english word in the decrypted text

compile:
```
gcc caesar.c hashtable.c run.c -o caesar
```
The encrypted text is taken from `stdin`, so you could just redirect a file to it like
```
./caesar < ciphertext.txt
```

This would output the encrypted text and the best guessed key
