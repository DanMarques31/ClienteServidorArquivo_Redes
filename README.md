# ClienteServidorArquivo_Redes
Alunos : Daniel Luiz e Lucas Ferreira

O programa foi desenvolvido em linux Ubuntu 22.04 LTS utilizando WSL 2 

Compilação: 

Para a compilação foi criado um makefile, basta executar o comando "make" que ambos cliente e servidor irão ser compilados.

Execução:

Para execução deverá ser aberto 2 terminais no mesmo diretório.
Antes de tudo no primeiro terminal deverá ser executado o servidor com seus respectivos parâmetros: 

      ./server porta_do_servidor tamanho_do_buffer

No outro terminal deverá ser executado o client com seus respectivos parâmetros: 

      ./client host_do_servidor porta_do_servidor nome_arquivo.txt tamanho_do_buffer

Parâmetros:

      Os parâmetros devem seguir essa ordem para o funcionamento. 
      Os parâmetros 'porta_do_servidor' e 'tamanho_do_buffer' deve ser o mesmo para ambos programas. 
      O parâmentro 'host_do_servidor' deverá ser locahost já que estão sendo executados em uma mesma máquina.
      E por fim o parâmetro 'nome_arquivo.txt' pode ser qualquer arquivo txt para teste. 
      Na pasta foram enviados dois arquivos caso queira testa-los = arquivo5MB.txt e arquivo20MB.txt com 5 megas e 20 megas respectivamente.
