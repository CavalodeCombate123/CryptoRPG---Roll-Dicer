# CryptoRPG---Roll-Dicer
CryptoRPG é uma aplicação desktop para Windows desenvolvida em C++ com Qt 6. O sistema permite rolagens de dados no formato clássico de RPG's, com suporte a múltiplos grupos de dados, modificadores fixos e histórico de resultados.  A aplicação utiliza geração de números baseada em std::random_device, visando maior imprevisibilidade nas rolagens.

Funcionalidades

Interpretação de expressões no formato:
- 3d8
- 2d20+5
- 4d6+2d8-3

  
- Suporte a múltiplos grupos de dados na mesma expressão

- Suporte a modificadores fixos positivos e negativos

- Exibição detalhada dos resultados individuais de cada dado

- Histórico completo das rolagens

- Interface gráfica personalizada com Qt

- Empacotamento para distribuição via instalador (Inno Setup)

Tecnologias Utilizadas:
C++
Qt 6 (Widgets)
CMake
MinGW 64-bit
Inno Setup (instalador Windows)

Como Funciona:
Entrada
O usuário fornece uma expressão no formato:
XdY + NdM - K

Onde:
X = quantidade de dados
Y = número de lados
+N ou -N = modificador fixo

exemplo:
3d8+2d10-5

Processamento:
A expressão é normalizada.
Cada grupo XdY é interpretado.
Os dados são gerados usando std::random_device.
O modificador é aplicado ao final.
O resultado detalhado e a soma total são retornados.

-----------

(Compilação)
Requisitos

Qt 6.x
MinGW 64-bit
CMake
Compilar em Release
No Qt Creator:
Alterar Build Configuration para Release
Executar Rebuild Project
O executável será gerado na pasta:
build-Desktop_Qt_6_x_x_MinGW_64_bit-Release


-----------

Distribuição

Para distribuição no Windows:
Copiar o .exe gerado (Release) para uma nova pasta.
Executar:
windeployqt CryptoRPG.exe
Criar instalador com Inno Setup usando a pasta final como fonte.
Gerar arquivo CryptoRPG_Setup.exe.

----------

Instalação

Executar CryptoRPG_Setup.exe.
Seguir as instruções do instalador.
O aplicativo será instalado em Program Files.
Atalhos serão criados no Menu Iniciar e opcionalmente na Área de Trabalho.

---------

Segurança

A geração de números utiliza std::random_device.
Não utiliza geradores pseudoaleatórios simples como rand().
Não realiza comunicação em rede.
Não coleta dados do usuário.

---------

Autor

Nome: Arthur do Nascimento Vale
Projeto desenvolvido para uso em mesas de RPG e estudo de desenvolvimento em C++ com Qt.
