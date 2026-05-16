// Endereço de memória para o buffer de texto VGA
unsigned char *vga_buffer = (unsigned char *)0xB8000;

void kernel_main() {
    const char *str = "DoorsOS-Core loaded with success!";
    int i = 0;
    int j = 0;

    // Limpa a tela (preenche com espaços)
    for (i = 0; i < 80 * 25 * 2; i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i+1] = 0x07; // Cor branca sobre fundo preto
    }

    // Escreve a string na tela
    i = 0;
    while (str[i] != '\0') {
        vga_buffer[j] = str[i];     // Caractere
        vga_buffer[j+1] = 0x0A;     // Atributo de cor (Verde)
        i++;
        j += 2;
    }

    while(1); // Loop infinito para manter o kernel rodando
}