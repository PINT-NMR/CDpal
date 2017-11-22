#ifndef FITDIFF_H
#define FITDIFF_H
#include "globals.h"

struct CDdiffFitmrq {
    int ndata, ma, mfit;
    std::vector< double > &x,&y,&sig;
    int ndone, itmax;
    double tol;
    void (*funcs)(const double, std::vector< double > &, double &, std::vector< double > &);
    std::vector< bool > ia;
    std::vector< double > a;
    std::vector< std::vector< double > > covar;
    std::vector< std::vector< double > > alpha;
    double chisq;

    CDdiffFitmrq(std::vector< double > &xx, std::vector< double > &yy, std::vector< double > &ssig, std::vector< double > &aa,
       std::vector< bool > &iia, void funks(const double, std::vector< double > &, double &, std::vector< double > &), const double
       TOL=1.e-3, const int NDONE=4, const int ITMAX=1000) : ndata(xx.size()), ma(aa.size()), x(xx), y(yy), sig(ssig),
          ndone(NDONE), itmax(ITMAX), tol(TOL), funcs(funks), ia(ma),
          a(aa), covar(ma,std::vector<double>(ma,0)), alpha(ma,std::vector<double>(ma,0))
    {
            for (int i=0;i<ma;i++) ia[i] = iia[i];
    }

    void hold(const int i, const double val) {ia[i]=false; a[i]=val;}
    void free(const int i) {ia[i]=true;}
    void invertMatrix2(std::vector< std::vector< double > >  &temp, std::vector< std::vector< double > >  &unitVec)
    {
        double d1,d2,d3;
        int column=0,row=0,n=temp.size(),m=unitVec[0].size();
        std::vector< int > Col(n),Row(n),Pivot(n);
        for (int i=0; i<n; i++)
            Pivot[i]=0;
        for (int i=0; i<n; i++)
        {
            d1=0.0;
            for (int j=0; j<n; j++)
                if (Pivot[j] != 1)
                    for (int k=0; k<n; k++)
                    {
                        if (Pivot[k] == 0)
                        {
                            if (abs(temp[j][k])>= d1)
                            {
                                d1=abs(temp[j][k]);
                                row=j;
                                column=k;
                            }
                        }
                    }
            Pivot[column]+=1;
            if (row != column)
            {
                for (int k=0; k<n; k++)
                    std::swap(temp[row][k],temp[column][k]);
                for (int k=0; k<m; k++)
                    std::swap(unitVec[row][k],unitVec[column][k]);
            }
            Row[i]=row;
            Col[i]=column;
            if (temp[column][column] == 0.0)
            {
                extern QString matrixError;
                matrixError = "Singular matrix, recheck your starting parameters.";
                return;
            }
            d3=1.0/temp[column][column];
            temp[column][column]=1.0;
            for (int k=0; k<n; k++)
                temp[column][k] *= d3;
            for (int k=0; k<m; k++)
                unitVec[column][k] *= d3;
            for (int k=0; k<n; k++)
                if (k != column)
                {
                    d2=temp[k][column];
                    temp[k][column]=0.0;
                    for (int l=0; l<n; l++)
                        temp[k][l] -= temp[column][l]*d2;
                    for (int l=0; l<m; l++)
                        unitVec[k][l] -= unitVec[column][l]*d2;
                }
        }
        for (int k=n-1; k>=0; k--)
        {
            if (Row[k] != Col[k])
                for (int l=0; l<n; l++)
                    std::swap(temp[l][Row[k]],temp[l][Col[k]]);
        }
    }

    void fit() {
        int j,k,l,iter,done=0;
        double alamda=.001,ochisq;
        std::vector< double > atry(ma),beta(ma),da(ma);
        mfit=0;
        for (j=0;j<ma;j++) if (ia[j]) mfit++;
        std::vector< std::vector< double > > oneda(mfit,std::vector<double>(1,0)), temp(mfit,std::vector<double>(mfit,0));
        mrqcof(a,alpha,beta);
        for (j=0;j<ma;j++) atry[j]=a[j];
        ochisq=chisq;
        for (iter=0;iter<itmax;iter++) {
            if (done==ndone) alamda=0.;
            for (j=0;j<mfit;j++) {
                for (k=0;k<mfit;k++) covar[j][k]=alpha[j][k];
                covar[j][j]=alpha[j][j]*(1.0+alamda);
                for (k=0;k<mfit;k++) temp[j][k]=covar[j][k];
                oneda[j][0]=beta[j];
            }
            if(mfit>0)
                invertMatrix2(temp,oneda);
            extern QString matrixError;
            if(matrixError!="")
                return;
            for (j=0;j<mfit;j++) {
                for (k=0;k<mfit;k++) covar[j][k]=temp[j][k];
                da[j]=oneda[j][0];
            }
            if (done==ndone) {
                covsrt(covar);
                covsrt(alpha);
                return;
            }
            for (j=0,l=0;l<ma;l++)
                if (ia[l]) atry[l]=a[l]+da[j++];
            mrqcof(atry,covar,da);
            if (abs(chisq-ochisq) < std::max(tol,tol*chisq)) done++;
            if (chisq < ochisq) {
                alamda *= 0.1;
                ochisq=chisq;
                for (j=0;j<mfit;j++) {
                    for (k=0;k<mfit;k++) alpha[j][k]=covar[j][k];
                        beta[j]=da[j];
                }
                for (l=0;l<ma;l++) a[l]=atry[l];
            } else {
                alamda *= 10.0;
                chisq=ochisq;
            }
        }
        extern QString matrixError;
        matrixError = "Too many iterations!\nRecheck your start parameters.";
    }


    void mrqcof(std::vector< double > &a, std::vector< std::vector< double > > &alpha, std::vector< double > &beta) {
        int i,j,k,l,m;
        double ymod,wt,sig2i,dy;
        std::vector< double > dyda(ma);
        for (j=0;j<mfit;j++) {
            for (k=0;k<=j;k++) alpha[j][k]=0.0;
            beta[j]=0.;
        }
        chisq=0.;
        for (i=0;i<ndata;i++) {
            funcs(x[i],a,ymod,dyda);
            sig2i=1.0/(sig[i]*sig[i]);
            dy=y[i]-ymod;
            for (j=0,l=0;l<ma;l++) {
                if (ia[l]) {
                    wt=dyda[l]*sig2i;
                    for (k=0,m=0;m<l+1;m++)
                        if (ia[m]) alpha[j][k++] += wt*dyda[m];
                    beta[j++] += dy*wt;
                }
            }
            chisq += dy*dy*sig2i;
        }
        for (j=1;j<mfit;j++)
            for (k=0;k<j;k++) alpha[k][j]=alpha[j][k];
    }

    void covsrt(std::vector< std::vector< double > > &covar) {
        int i,j,k;
        for (i=mfit;i<ma;i++)
            for (j=0;j<i+1;j++) covar[i][j]=covar[j][i]=0.0;
        k=mfit-1;
        for (j=ma-1;j>=0;j--) {
            if (ia[j]) {
                for (i=0;i<ma;i++) std::swap(covar[i][k],covar[i][j]);
                for (i=0;i<ma;i++) std::swap(covar[k][i],covar[j][i]);
                k--;
            }
        }
    }

    // This is the public gridsearch
    void gridSearch(std::vector< double > &aLo, std::vector< double > &aHi, std::vector< int > &aSteps, bool fgrid) {
       if (fgrid) {
           std::vector< double > aAct(aLo);
           gridSearch(aLo, aHi, aSteps, aAct, 0);
       }
    }

    // NOTE THIS VERSION SHOULD ONLY BE USED WITHIN THE CLASS
    void gridSearch(std::vector< double > &aLo, std::vector< double > &aHi, std::vector< int > &aSteps, std::vector< double > &aAct, int index)
    {
        static double chisqLo = -1.;
        static std::vector< double > dyda(ma);
        double chisqGrid, yGrid;

        for (int i=0; i<aSteps[index]; i++) {
            if ((uint) index == a.size()-1) {
               //cout << aAct[0] << " " << aAct[1] << " " << aAct[2] << " " << aAct[3] << " " << aAct[4] << " " << aAct[5] << endl;
               chisqGrid = 0.;
               for (int j=0; j<ndata; j++) {
                  funcs(x[j], aAct, yGrid, dyda);
                  chisqGrid += (yGrid -y[j]/sig[j])*(yGrid -y[j]/sig[j]);
               }

               if (chisqGrid < chisqLo || chisqLo == -1.) {
                   chisqLo = chisqGrid;
                   a = aAct;
               }
            }
            else {
               gridSearch(aLo, aHi, aSteps, aAct, index+1);
            }
            if(index == 2)
                aAct[index] += aAct[index]*1.05;
            else
                aAct[index] += (aHi[index]-aLo[index])/(double)(aSteps[index]-1);
        }
        aAct[index] = aLo[index];
    }
};



#endif // FITDIFF_H
