# FSO-2024.1
 Repositório para a matéria de Fundamentos de Sistemas Operacionais
 
 Namoral, esse ngc de anotar a aula em .md n funciona

## Métodos de Avaliação

## Aulas

### Aula 05 (01/04) - Processos

**Troca de contexto:** processo de preservar informações do processador/processo atual em mudanças de processos <br>
**Processos com concorrência:** As vezes, executar mais um processo ao mesmo tempo pode ser mais rápido = Pipeline em FAC <br>

#### **Escalonamento**
* Escolher qual 

*-----------TERMINAR-----------*

#### **Critérios de Escalonamento**
Não é possível atingir/aplicar todos esses critérios ao mesmo tempo
* Minimizar tempo de resposta
* Minimizar tempo de turnaround
* Minimizar waiting time
* Maximizar throughput

#### **Algoritmos de Escalonamento**

**First Come First Served**<br>
* Funciona como uma pilha (FIFO)
* Todo processo passa pelo ciclo de etapas de processo (rodando -> bloqueado -> pronto), então para cada processo na "fila" temos um ciclo para esse processo
* Conforme um processo passa pela sua etapa de execução e causa seu proprio bloqeuio, ele vai para o final da "fila"
* Tempo de Espera = Tempo de Serviço – Tempo de Chegada

| Vantagens | Desvantagens |
| ----------| ------------ |
|Fácil de Implementar| Sem previsão para o inicio de um processo|
| CPU está sempre em uso, isso é considerado eficiente | principio de justiça nem sempre é respeitado, pois processos que usam mais a cpu estão em vantagem|

**Round-Robin (ou Espera Circular)**<br>
* Todo processo tem o direito de usar a CPU por um tempo definido = **Quantum** -> Princípio de Justiça
* Um quantum mto longo causa um comportamento igual ao First Come First Served (FCFS)
* Quantum mto curto -> problemas como perda de eficiência (pq?)
* Maior problema = dimensionar o quantum
* Para o algoritmo ser eficiente -> tempo de troca de contexto << tempo de execução

**Escalonamento por Prioridades**
* Existem processos com prioridades diferentes
* É usado em OS de tempo real

    **Prioridade dinâmica**
    
    <br>
    
    **Prioridade Estática:**

*-----------TERMINAR-----------*


**Escalonamento por Shortest Job First**
* Assim como quando um processo é criado, ele vem com um atributo de prioridade, ele também vem com um atributo de tempo de execução
* Problema da parada = Indecidível = Matemáticamente impossível

*-----------TERMINAR-----------*

**Escalonamento em Dois Níveis**
* Consiste em aplicar regras diferentes para conjuntos difrentes de processos

Tanenbaum - Coomeçar o cap. 2

Machado e Maia - Caps. 5 e 8

### Aula 06 (03/04) - Threads
Perdi essa aula pq tava com dengue, ent vou só resumir o que eu for lendo dos slides por enquanto
### Aula 07 (08/04) - Threads
Perdi essa aula pq tava com dengue, ent vou só resumir o que eu for lendo dos slides por enquanto
