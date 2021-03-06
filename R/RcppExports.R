# This file was generated by Rcpp::compileAttributes
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

col_mixture_gibbs <- function(ryo, rxo, rxa, rlam, rpriorprob, rburnin, rniter, ralpha) {
    .Call('oda_col_mixture_gibbs', PACKAGE = 'oda', ryo, rxo, rxa, rlam, rpriorprob, rburnin, rniter, ralpha)
}

col_normal_em_soft <- function(ryo, rxo, rxa, rlam, rpriorprob) {
    .Call('oda_col_normal_em_soft', PACKAGE = 'oda', ryo, rxo, rxa, rlam, rpriorprob)
}

col_normal_em <- function(ryo, rxo, rxa, rlam, rpriorprob) {
    .Call('oda_col_normal_em', PACKAGE = 'oda', ryo, rxo, rxa, rlam, rpriorprob)
}

col_normal_gibbs <- function(ryo, rxo, rxa, rlam, rpriorprob, rburnin, rniter) {
    .Call('oda_col_normal_gibbs', PACKAGE = 'oda', ryo, rxo, rxa, rlam, rpriorprob, rburnin, rniter)
}

col_normal_var <- function(ryo, rxo, rxa, rlam, rpriorprob) {
    .Call('oda_col_normal_var', PACKAGE = 'oda', ryo, rxo, rxa, rlam, rpriorprob)
}

mixture_gibbs <- function(ryo, rxo, rxa, rlam, rpriorprob, rburnin, rniter, ralpha) {
    .Call('oda_mixture_gibbs', PACKAGE = 'oda', ryo, rxo, rxa, rlam, rpriorprob, rburnin, rniter, ralpha)
}

mixture_var <- function(ryo, rxo, rxa, rd, rlam, rpriorprob, ralpha, rrho_min, ranneal_steps) {
    .Call('oda_mixture_var', PACKAGE = 'oda', ryo, rxo, rxa, rd, rlam, rpriorprob, ralpha, rrho_min, ranneal_steps)
}

normal_em <- function(ryo, rxo, rxa, rd, rlam, rpriorprob) {
    .Call('oda_normal_em', PACKAGE = 'oda', ryo, rxo, rxa, rd, rlam, rpriorprob)
}

normal_gibbs <- function(ryo, rxo, rxa, rd, rlam, rpriorprob, rburnin, rniter) {
    .Call('oda_normal_gibbs', PACKAGE = 'oda', ryo, rxo, rxa, rd, rlam, rpriorprob, rburnin, rniter)
}

normal_var <- function(ryo, rxo, rxa, rd, rlam, rpriorprob, rrho_min, ranneal_steps) {
    .Call('oda_normal_var', PACKAGE = 'oda', ryo, rxo, rxa, rd, rlam, rpriorprob, rrho_min, ranneal_steps)
}

probit_normal_gibbs <- function(rbit, rxo, rxa, rd, rlam, rpriorprob, rburnin, rniter) {
    .Call('oda_probit_normal_gibbs', PACKAGE = 'oda', rbit, rxo, rxa, rd, rlam, rpriorprob, rburnin, rniter)
}

rcpparma_hello_world <- function() {
    .Call('oda_rcpparma_hello_world', PACKAGE = 'oda')
}

rcpparma_outerproduct <- function(x) {
    .Call('oda_rcpparma_outerproduct', PACKAGE = 'oda', x)
}

rcpparma_innerproduct <- function(x) {
    .Call('oda_rcpparma_innerproduct', PACKAGE = 'oda', x)
}

rcpparma_bothproducts <- function(x) {
    .Call('oda_rcpparma_bothproducts', PACKAGE = 'oda', x)
}

sum_gibbs <- function(ryo, rxo, rxs, rlam, rpriorprob, rburnin, rniter) {
    .Call('oda_sum_gibbs', PACKAGE = 'oda', ryo, rxo, rxs, rlam, rpriorprob, rburnin, rniter)
}

xa_LDLT <- function(rxo, repsilon) {
    .Call('oda_xa_LDLT', PACKAGE = 'oda', rxo, repsilon)
}

