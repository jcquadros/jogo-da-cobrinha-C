# Jogo da Cobrinha em C
Trata-se do meu primeiro trabalho de faculdade

## Como Jogar:
* Baixar todos os arquivos;
* Garanta que o arquivo JullieDeCastroQuadros.c esteja ao lado da pasta Casos
* Abra a pasta no terminal do linux (clicar com botao direito e "abrir com terminal")
* Compile o arquivo JullieDeCastroQuadros.c digitando o seguinte comando : gcc -o jogo JullieDeCastroQuadros.c.
* Informe a fase que deseja jogar : 
Funciona da seguinte forma. Temos 3 modos de jogo: simples, normal e bonus. E cada modo de jogo há uma quantidade específica de fases enumeradas dentro da pasta. Para 
jogar, basta informar o diretorio de jogo da seguinte forma : Casos/Testes/MODO_DE_JOGO/NUMERO_DA_FASE

**Ex:./jogo Casos/Testes/simples/1**

**Ex:./jogo Casos/Testes/normais/10**

* Aperte as teclas 'c', 'a' e 'h' para a movimentação da cobrinha em frente, sentido anti-horário e sentido horário respectivamente.
* Coma frutinhas '*' para fazer a cobrinha crescer, dinheiro '$' para acumular pontos e evite as paredes '#'! Elas podem te matar. Dentro das fases bônus há uma novidade: Os tuneis 
teleportam a cobrinha. 


## Funcionalidades Extras (Pedidas pelo professor para a correção do trabalho)
Você pode executar jogadas automáticas por meio do redirecionamento de entrada de modo que não precise digitar nada. Muita coisa, mas acalme-se, é opcional!
Basta vc digitar na frente do diretório o endereço do arquivo com os movimentos/jogadas a serem executados. Esse arquivo encontra-se por padrão dentro da pasta da fase, chama-se movimentos.txt. Assim basta realizarmos o redirecionamento de entrada dessa forma:

**./jogo Casos/Testes/simples/1 <Casos/Testes/simples/1/movimentos.txt**

Simples!

Há também outra funcionalidade que permite corrigir o trabalho (ver se tudo está funcionando como realmente deveria). Para isso deve-se realizar o redirecionamento de entrada juntamente com o de saida. Dessa forma:

**./jogo Casos/Testes/simples/1 <Casos/Testes/simples/1/movimentos.txt >Casos/Testes/simples/1/saida/saida.txt**

E por ultimo executar o diff pelo terminal ou utilizar o meld para comparar as saidas. Aqui ensino a utilizar o diff pelo terminal mesmo. Nesse caso digite:

**diff Casos/Testes/simples/1 Casos/Gabarito/simples/1**

Sim, é só alterar o diretório Testes para Gabarito. Se nenhuma mensagem aparecer no terminal então o jogo foi executado com êxito e não foi achado erro algum.

**Com isso encerro aqui. Agora é só se divertir! :)**
