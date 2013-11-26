#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/sched.h>

asmlinkage long sys_mycall(pid_t pid) {
  struct task_struct *task, *mytask = NULL;
  struct sched_param sp;
  int rt_priority = 1, ret;

  for_each_process(task) {

    if (task->pid == pid)
      mytask = task;
    else {
      if (task->policy == SCHED_FIFO || task->policy == SCHED_RR) 
    	// Obtém a maior prioridade dentre as de todos os processos RT, à exceção daquele passado como argumento.
    	if (task->rt_priority > rt_priority)
      	  rt_priority = task->rt_priority;
    }
  }
  // Erro: processo não encontrado.
  if (mytask == NULL)
    return 1;

  // Se possível, incrementa a prioridade.
  if (rt_priority < 99)
    rt_priority++;

  sp.sched_priority = rt_priority;
  ret = sched_setscheduler(mytask, SCHED_FIFO, &sp);

  // Erro: não foi possível alterar o escalonamento do processo.
  if (ret == -1)
    return 2;

  return 0;
}
