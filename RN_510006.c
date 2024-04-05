#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct No{
    int chave;
    char cor;
    struct No *pai, *esq, *dir;
}no;

no *externo;

void RotacaoE(no *z, no **ptraiz);
void RotacaoD(no *z, no **ptraiz);
void RotaRN(no **z, no **ptraiz);
void InserirRN(int chave, no **ptraiz);
void MoverPai(no **u, no **v, no **ptraiz);
no* Buscar(int chave, no *pt);
no* sucessor(no *z);
void RotaRemoverRN(no **x, no **ptraiz);
void RemoverRN(int chave, no **ptraiz);
int ContNo (no *ptraiz);
int AlturaNegraDir(no *x);
int AlturaNegraEsq(no *x);
void E_RN(no *x, bool *e_RN);

int main()
{
    srand(time(NULL));
    externo = (no*)malloc(sizeof(no));

    externo->chave = -1;
    externo->cor = 'N';
    externo->pai = externo;

    bool e_RN = true;
    int qtdNo;
    no *ptraiz[1000] = {[0 ... 999] = externo}; //VETOR QUE ARMAZENARA AS RAIZES DAS ARVORES CRIADAS
    int *vet;
    int qtdArv = 100;
    int InsNos = 100;
    int RemNos = 10;

    vet = malloc(InsNos * (sizeof(int))); //VETOR QUE GUARDARA AS CHAVES INSERIDAS PARA UTILIZA-LAS NO REMOVER

    for (int i = 0; i < qtdArv; i++)
    {
        ptraiz[i]->pai = externo;
        ptraiz[i]->cor = 'N';
    }

    for(int i = 0; i < qtdArv; i++)
    {
        
        for(int k = 0; k < InsNos; k++)
        {
            vet[k] = -1;
        }

        int q = 0;
        while(q < InsNos)
        {
            int x = rand() % 100000;
            int z = 0;
            int n = 0;
            while(z == 0 && n < InsNos)
            {
                if (vet[n] == x)
                {
                    z = 1;
                }
                n++;
            }

            if (z == 0)
            {
                vet[q] = x;
            }
            else
            {
                q--;
            }
            q++;
        }

        //INSERINDO OS NOS
        for(int k = 0; k < InsNos; k++)
        {
            InserirRN(vet[k], &ptraiz[i]);
        }

        //APOS A INSERCAO, VERIFICA SE A ARVORE EH RUBRO-NEGRA E A QUANTIDADE DE NOS
        qtdNo = ContNo(ptraiz[i]);
        printf("\nRN %d INSERIR\nquantidade de Nos = %d\n", i+1, qtdNo);
        
        E_RN(ptraiz[i], &e_RN);
        if (e_RN)
        {
            printf("E RN\n");
        }
        else
        {
            printf("NAO E RN\n");
        }

        //REMOVENDO OS NOS
        for(int k = 0; k < RemNos; k++)
        {
            RemoverRN(vet[k], &ptraiz[i]);
        }

        //APOS A REMOCAO, VERIFICA SE A ARVORE AINDA EH RUBRO-NEGRA E A QUANTIDADE DE NOS
        qtdNo = ContNo(ptraiz[i]);
        printf("\nRN %d REMOVER\nquantidade de Nos = %d\n", i+1, qtdNo);

        E_RN(ptraiz[i], &e_RN);
        if (e_RN)
        {
            printf("E RN\n");
        }
        else
        {
            printf("NAO E RN\n");
        }

    }

    return 0;
}
    
void RotacaoE(no *z, no **ptraiz)
{
    no *aux = z->dir;
    z->dir = aux->esq;

    if (aux->esq != externo)
    {
        aux->esq->pai = z;
    }

    aux->pai = z->pai;

    if (z->pai == externo)
    {
        (*ptraiz) = aux;
    }
    else
    {
        if (z == z->pai->esq)
        {
            z->pai->esq = aux;
        }
        else
        {
            z->pai->dir = aux;
        }
    }

    aux->esq = z;
    z->pai = aux;
}

void RotacaoD(no *z, no **ptraiz)
{
    no *aux = z->esq;
    z->esq = aux->dir;

    if (aux->dir != externo)
    {
        aux->dir->pai = z;
    }

    aux->pai = z->pai;

    if (z->pai == externo)
    {
        (*ptraiz) = aux;
    }
    else
    {
        if (z == z->pai->dir)
        {
            z->pai->dir = aux;
        }
        else
        {
            z->pai->esq = aux;
        }
    }

    aux->dir = z;
    z->pai = aux;
}

void RotaRN(no **z, no **ptraiz)
{
    no *y;

    while ((*z)->pai->cor == 'R')
    {
        if ((*z)->pai == (*z)->pai->pai->esq)
        {
            y = (*z)->pai->pai->dir;
            if (y->cor == 'R')
            {
                (*z)->pai->cor = 'N';
                y->cor = 'N';
                (*z)->pai->pai->cor = 'R';
                (*z) = (*z)->pai->pai;
            }
            else
            {
                if ((*z) == (*z)->pai->dir)
                {
                    (*z) = (*z)->pai;
                    RotacaoE((*z), ptraiz);
                }
                (*z)->pai->cor = 'N';
                (*z)->pai->pai->cor = 'R';
                RotacaoD((*z)->pai->pai, ptraiz);
            }
        }
        else
        {
            y = (*z)->pai->pai->esq;
            if (y->cor == 'R')
            {
                (*z)->pai->cor = 'N';
                y->cor = 'N';
                (*z)->pai->pai->cor = 'R';
                (*z) = (*z)->pai->pai;
            }
            else
            {
                if ((*z) == (*z)->pai->esq)
                {
                    (*z) = (*z)->pai;
                    RotacaoD((*z), ptraiz);
                }
                (*z)->pai->cor = 'N';
                (*z)->pai->pai->cor = 'R';
                RotacaoE((*z)->pai->pai, ptraiz);
            }
        }
    }
    (*ptraiz)->cor = 'N';
}

void InserirRN(int chave, no **ptraiz)
{
    no *y = externo;
    no *pt = (*ptraiz);

    while (pt != externo)
    {
        y = pt;
        if (chave == pt->chave)
        {
            //chave existente
            y = NULL;
            pt = externo;
        }
        else if (chave < pt->chave)
        {
            pt = pt->esq;
        }
        else
        {
            pt = pt->dir;
        }
    }

    if (y != NULL)
    {

        no* z = (no*)malloc(sizeof(no));
        z->chave = chave;
        z->pai = y;

        if (y == externo)
        {
            (*ptraiz) = z;
        }
        else if (z->chave < y->chave)
        {
            y->esq = z;
        }
        else
        {
            y->dir = z;
        }
        
        z->esq = externo;
        z->dir = externo;
        z->cor = 'R';
        RotaRN(&z, ptraiz);
    }
}

void MoverPai(no **u, no **v, no **ptraiz)
{
    if ((*u)->pai == externo)
    {
        (*ptraiz) = (*v);
    }
    else if ((*u) == (*u)->pai->esq)
    {
        (*u)->pai->esq = (*v);
    }
    else
    {
        (*u)->pai->dir = (*v);
    }

    (*v)->pai = (*u)->pai;
}

no* Buscar(int chave, no *pt) 
{
    if((pt == externo) || (pt->chave == chave))
    {
        return pt;
    }
    else if(pt->chave < chave)
    {
        return Buscar(chave, pt->dir);
    }
    else
    {
        return Buscar(chave, pt->esq);
    }
}

no* sucessor(no *z) 
{
    if (z->dir != externo)
    {
        no *aux = z->dir;
        while (aux->esq != externo)
        {
            aux = aux->esq;
        }

        return aux;
    }

    no* y = z->pai;

    while (y != externo && z == y->dir)
    {
        z = y;
        y = y->pai;
    }

    return z;
}

void RotaRemoverRN(no **x, no **ptraiz)
{
    no *w;

    while (((*x) != (*ptraiz)) && ((*x)->cor != 'R'))
    {
        if ((*x) == (*x)->pai->esq)
        {
            w = (*x)->pai->dir;

            if(w->cor == 'R')
            {
                (*x)->pai->cor = 'R';
                w->cor = 'N';
                RotacaoE((*x)->pai, ptraiz);
                w = (*x)->pai->dir;
            }

            if ((w->dir->cor == 'N') && (w->esq->cor == 'N'))
            {
                w->cor = 'R';
                (*x) = (*x)->pai;
            }
            else
            {
                if (w->dir->cor == 'N')// //
                {
                    w->esq->cor = 'N';
                    w->cor = 'R';
                    RotacaoD(w, ptraiz);
                    w = (*x)->pai->dir;
                }

                w->cor = (*x)->pai->cor;
                (*x)->pai->cor = 'N';
                w->dir->cor = 'N';
                RotacaoE((*x)->pai, ptraiz);
                (*x) = (*ptraiz);
            }
        }
        else
        {
            w = (*x)->pai->esq;

            if(w->cor == 'R')
            {
                (*x)->pai->cor = 'R';
                w->cor = 'N';
                RotacaoD((*x)->pai, ptraiz);
                w = (*x)->pai->esq;
            }

            if ((w->esq->cor == 'N') && (w->dir->cor == 'N'))
            {
                w->cor = 'R';
                (*x) = (*x)->pai;
            }
            else
            {
                if (w->esq->cor == 'N') // //
                {
                    w->dir->cor = 'N';
                    w->cor = 'R';
                    RotacaoE(w, ptraiz);
                    w = (*x)->pai->esq;
                }

                w->cor = (*x)->pai->cor;
                (*x)->pai->cor = 'N';
                w->esq->cor = 'N';
                RotacaoD((*x)->pai, ptraiz);
                (*x) = (*ptraiz);
            }
        }
    }
    (*x)->cor = 'N';
}

void RemoverRN(int chave, no **ptraiz)
{
    no *z = (*ptraiz);
    z = Buscar(chave, z);

    if (z == externo)
    {
        //elemento nao existe
        return;
    }

    no *y = z;
    no *x;
    char corOriginal = y->cor;

    if (y->esq == externo) 
    {
        x = z->dir;
        MoverPai(&z, &(z->dir), ptraiz);
    }
    else if (y->dir == externo) 
    {
        x = z->esq;
        MoverPai(&z, &(z->esq), ptraiz);
    }
    else
    {
        y = sucessor(z);
        corOriginal = y->cor;
        x = y->dir;

        if (y->pai != z)
        {
            MoverPai(&y, &(y->dir), ptraiz);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        else
        {
            x->pai = y;
        }
        MoverPai(&z, &y, ptraiz);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }
    

    free(z);

    if (corOriginal == 'N')
    {
        RotaRemoverRN(&x, ptraiz);
    }

    
}

int ContNo (no *ptraiz)
{
    if (ptraiz == externo)
    {
        return 0;
    }
    else
    {
        return 1 + ContNo(ptraiz->esq) + ContNo(ptraiz->dir);
    }
}

int AlturaNegraDir(no *x)
{
    if(x == externo)
    {
        return 0;
    }
    else
    {
        int dir = AlturaNegraDir(x->dir);
        if(x->cor == 'N')
        {
            return dir + 1;
        }
        else 
        {
            return dir;
        }
    }
}

int AlturaNegraEsq(no *x)
{
    if(x == externo)
    {
        return 0;
    }
    else
    {
        int esq = AlturaNegraEsq(x->esq);
        if(x->cor == 'N')
        {
            return esq + 1;
        }
        else 
        {
            return esq;
        }
    }
}

void E_RN(no *x, bool *e_RN)
{
    if(x != externo && e_RN)
    {
        E_RN(x->esq, e_RN);
        E_RN(x->dir, e_RN);

        int esq = AlturaNegraEsq(x->esq);
        int dir = AlturaNegraDir(x->dir);
        
        if(esq != dir)
        {
            (*e_RN) = false;
        }
    }
}
