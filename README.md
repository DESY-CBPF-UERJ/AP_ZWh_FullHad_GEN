# ![channel](feynman_diagram.svg)

# **Analysis project for the hadronic channel of the bb(h/Z)+DM search using data from Run 3.**

Primeiro baixe a versão mais atualizada do HepHero

```bash
git clone https://github.com/DESY-CBPF-UERJ/HEPHero.git
```
Siga todos os passos presentes no "QuickStart" do HepHero, mas pare a etapa do setup. Acesse a pasta do HepHero
```bash
cd HEPHero
```
Dentro da pasta do HepHero, baixe o seu projeto, no nosso caso, é o AP_bbhZDM_Had_R3
```bash
git clone https://github.com/DESY-CBPF-UERJ/AP_bbhZDM_Had_R3.git
```

A partir daqui, você pode querer fazer duas coisas
* Executar seu projeto para adquirir os arquivos que serão trabalhados mais a frente
* Atualizar o projeto que está trabalhando (incluir features, funções e etc)


# Executando o projeto

Dentro da pasta do HepHero, mude o setup do projeto que está trabalhando, no nosso caso
```bash
python setAnalysis.py -a AP_bbhZDM_Had_R3
```
* Lembre-se de ter dado ```hepenv```!

A partir daqui, você executa o projeto como um projeto padrão do HepHero (veja o readme do HepHero para mais informações)


# Modificando o projeto (Trunk Based method)

Acesse a pasta do seu projeto, no nosso caso AP_bbhZDM_Had_R3

```bash
cd AP_bbhZDM_Had_R3
```
A partir daqui, todas as modificações que vier a fazer, vão estar relacionadas ao git do seu projeto. Foi determinado que esse projeto vai seguir a metodologia Trunk-based, então os passos a seguir são os que devem ser seguidos na hora de resolver um problema, ou mesmo incluir uma feature. Para exemplificar, os passos seguintes vão ser feitos, supondo que se queira remover um arquivo do projeto (mas os passos são os mesmos para qualquer alteração!).

1. Primeiro veja que arquivos estão modificados com relação ao projeto main atraves do comando status
```bash
git status
```
* Ele não deve acusar nenhum arquivo de diferente, caso acuse, garanta que esteja na main principal e que ela está atualizada:
```bash
git checkout main
git pull origin main
```
2. Crie uma branch de nome intuitivo e mude para ela:
```bash
git checkout -b remove/mydiff.diff
```
3. Faça a modificação que quer fazer (modificações pequenas), no meu caso ```rm mydiff.diff```
4. Faça commit das alterações
```bash
git add .
git commit -m "{informação do que foi mudado}"
```
* Altere o que está entre {} para explicar sua modificação!
5. Mude para o branch principal (main) e garanta que ele esteja atualizado!
```bash
git checkout main
git pull origin main
```
* Caso exista algum tipo de conflito, então você deve resolver ele antes de prosseguir

6. Sem que tenha conflito, basta dar merge da sua branch com o main
```bash
git merge remove/mydiff.diff
```
7. Apague todas as branchs locais que você criou
```bash
git branch -d remove/mydiff.diff     
```
* Para checar se há alguma branch ainda existente localmente
```bash
git branch
```

8. Aplique as modificações no repositorio git, através do comando:
```bash
git push origin
```
* Lembre-se de estar na sua branch ```main```

## (Implemnetado) Utilizando o ```.gitignore```
Quando se executava a etapa 1 (```git status````). Ele ausava que já existem arquivos modificados, como esses:
![image](https://github.com/user-attachments/assets/8299488d-aab9-4cc4-8d07-883e5ac62e0b)
* Esses arquivos já estavam modificados pois eles são parte da configuração que é feita no HepHero, e cada pessoa vai ter informações diferentes nesses arquivos. Para evitar confusão, foi utilizado o ```.gitignore```. Ele é responsável por indicar para o git que arquivos deve ignorar mudanças. A seguir estão os passso que foram utilizados
  1.1. Crie um arquivo, dentro da pasta AP_bbhZDM_Had_R3, chamado ```.gitignore``` indicando quais arquivos não devem ser considerados na hora de checar modificações, bem como enviar como atualização pra sua main. Crie o arquivo
```bash
vi .gitignore
```
  1.2. Dentro dela já vão exitir diversos arquivos que são ignorados, inclua o nome dos arquivos, indicando o path, a partir do diretorio do ```.gitignore```, no meu caso
```bash
ana/CMakeFiles/CMakeDirectoryInformation.cmake
ana/Makefile
ana/cmake_install.cmake
src/CMakeFiles/CMakeDirectoryInformation.cmake
src/Makefile
src/cmake_install.cmake
```








