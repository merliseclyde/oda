#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
List normal_gibbs(NumericVector ryo, NumericMatrix rxo, NumericMatrix rxa, NumericVector rlam, NumericVector rpriorprob, SEXP rburnin, SEXP rniter){

	//Define Variables//
	int niter=Rcpp::as<int >(rniter);
	int burnin=Rcpp::as<int >(rburnin);
	int p=rxo.ncol();
	int no=rxo.nrow();
	int na=rxa.ncol();
	double a=(no-1)/2;
	double b;
	double phi;
	Mat<double> xag;
	Mat<double> xaxa(p,p);
	Mat<double> xoxo(p,p);
	Mat<double> xoxog(p,p);
	Mat<double> D(p,p);
	Mat<double> Lam(p,p);
	Mat<double> Lamg(p,p);
	Mat<double> E(na,na);
	Mat<double> L(na,na);
	Mat<double> xog;
	Mat<double> Ino=eye(no,no);
	Mat<double> Ina=eye(na,na);
	Mat<double> P1(no,no);
	Mat<double> Px(no,no);
	Mat<double> ya_mcmc(na,niter,fill::zeros);
	Mat<double> prob_mcmc(p,niter,fill::zeros);
	Mat<uword>  gamma_mcmc(p,niter,fill::ones);
	Col<double> phi_mcmc(niter,fill::ones);
	Col<double> one(no,fill::ones);
	Col<double> mu(na);
	Col<double> ya(na);
	Col<double> Z(na);
	Col<double> d(p);
	Col<double> Bols(p);
	Col<double> xoyo(p);
	Col<double> prob(p,fill::ones);
	Col<double> priorodds(p);
	Col<double> odds(p);
	Col<double> ldl(p);
	Col<double> dli(p);
	Col<uword> gamma(p,fill::ones);
	Col<uword> inc_indices(p,fill::ones);


	//Copy RData Into Matrix Classes//
	arma::mat xo(rxo.begin(), no, p, false);
	arma::mat xa(rxa.begin(), na, p, false);
	arma::colvec yo(ryo.begin(), ryo.size(), false);
	arma::colvec lam(rlam.begin(),rlam.size(), false);
	arma::colvec priorprob(rpriorprob.begin(),rpriorprob.size(), false);


	//Create Matrices//
	xoyo=xo.t()*yo;
	xoxo=xo.t()*xo;
	xaxa=xa.t()*xa;
	D=xaxa+xoxo;
	d=D.diag();


	//Initialize Parameters at MLE//
	P1=one*(one.t()*one).i()*one.t();
	Px=xo*(xoxo).i()*xo.t();
	phi=(no-1)/dot(yo,((Ino-P1-Px)*yo));
	Bols=(xoxo).i()*xo.t()*yo;
	ya=xa*Bols;


	//Pre-Gibbs Computations Needn't Be Computed Every Iteration//
	Lam=diagmat(lam);
	for (int i = 0; i < p; ++i)
	{
		priorodds(i)=priorprob(i)/(1-priorprob(i));
		ldl(i)=sqrt(lam(i)/(d(i)+lam(i)));
		dli(i)=1/(d(i)+lam(i));
	}


	//Run Gibbs Sampler//
	ya_mcmc.col(0)=ya;
	phi_mcmc(0)=phi;
	gamma_mcmc.col(0)=gamma;
	prob_mcmc.col(0)=prob;
	for (int t = 1; t < niter; ++t)
	{
		//Form Submatrices
		inc_indices=find(gamma);
		Lamg=Lam.submat(inc_indices,inc_indices);
		xag=xa.cols(inc_indices);
		xog=xo.cols(inc_indices);
		xoxog=xoxo.submat(inc_indices,inc_indices);

		//Draw Phi//
		b=0.5*dot(yo,(Ino-P1-xog*(xoxog+Lamg).i()*xog.t())*yo);
		phi=R::rgamma(a,(1/b)); //rgamma uses scale

		//Draw Ya//
		mu=xag*(xoxog+Lamg).i()*xog.t()*yo;
		E=Ina+xag*(xoxog+Lamg).i()*xag.t();
		E=E/phi;
		L=chol(E);
		for (int i = 0; i < na; ++i) Z(i)=R::rnorm(0,1);
		ya=mu+L.t()*Z;

		//Draw Gamma//
		for (int i = 0; i < p; ++i)
		{
			Bols(i)=(1/d(i))*(xoyo(i)+dot(xa.col(i),ya));
			odds(i)=priorodds(i)*ldl(i)*trunc_exp(0.5*phi*dli(i)*d(i)*d(i)*Bols(i)*Bols(i));
			prob(i)=odds(i)/(1+odds(i));

			if(R::runif(0,1)<prob(i)){
				gamma(i)=1;
			}else{
				gamma(i)=0;
			}
		}

		//Store Draws//
		gamma_mcmc.col(t)=gamma;
		prob_mcmc.col(t)=prob;
		ya_mcmc.col(t)=ya;
		phi_mcmc(t)=phi;
	}


	return Rcpp::List::create(
			Rcpp::Named("phi_mcmc") = phi_mcmc,
			Rcpp::Named("prob_mcmc") = prob_mcmc,
			Rcpp::Named("prob") = mean(prob_mcmc.cols(burnin-1,niter-1),1),
			Rcpp::Named("gamma_mcmc") = gamma_mcmc,
			Rcpp::Named("ya_mcmc") = ya_mcmc
			) ;
}
