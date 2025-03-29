import os
from PIL import Image

# Diretório principal com as imagens
input_dir = r"c:\Users\Documentos\Downloads\MADOS"
output_dir = r"c:\Users\Documentos\Downloads\MADOS_png"

# Percorre todas as pastas e subpastas
for root, _, files in os.walk(input_dir):
    for filename in files:
        if filename.lower().endswith(".tif") or filename.lower().endswith(".tiff"):
            input_path = os.path.join(root, filename)

            # Criar estrutura de diretórios no destino
            relative_path = os.path.relpath(root, input_dir)
            output_subdir = os.path.join(output_dir, relative_path)
            os.makedirs(output_subdir, exist_ok=True)

            # Criar caminho de saída
            output_path = os.path.join(output_subdir, filename.rsplit(".", 1)[0] + ".png")

            # Converter e salvar sem perder qualidade
            img = Image.open(input_path)
            img.save(output_path, format="PNG", compress_level=0)

print("Conversão concluída!")
