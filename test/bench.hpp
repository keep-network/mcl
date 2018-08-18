void testBench(const G1& P, const G2& Q)
{
	G1 Pa;
	G2 Qa;
	Fp12 e1, e2;
	pairing(e1, P, Q);
	Fp12::pow(e2, e1, 12345);
	const int C = 500;
	const int C2 = 1000;
	const int C3 = 10000;
	Fp x, y;
	x.setHashOf("abc");
	y.setHashOf("xyz");
#if 1
	mpz_class z = 3;
	mpz_class a = x.getMpz();
	CYBOZU_BENCH_C("G1::mulCT     ", C, G1::mulCT, Pa, P, a);
//	CYBOZU_BENCH_C("G1::mulCTsmall", C, G1::mulCT, Pa, P, z);
	CYBOZU_BENCH_C("G1::mul       ", C, G1::mul, Pa, Pa, a);
//	CYBOZU_BENCH_C("G1::mulsmall  ", C, G1::mul, Pa, Pa, z);
	CYBOZU_BENCH_C("G1::add       ", C, G1::add, Pa, Pa, P);
	CYBOZU_BENCH_C("G1::dbl       ", C, G1::dbl, Pa, Pa);
	CYBOZU_BENCH_C("G2::mulCT     ", C, G2::mulCT, Qa, Q, a);
//	CYBOZU_BENCH_C("G2::mulCTsmall", C, G2::mulCT, Qa, Q, z);
	CYBOZU_BENCH_C("G2::mul       ", C, G2::mul, Qa, Qa, a);
//	CYBOZU_BENCH_C("G2::mulsmall  ", C, G2::mul, Qa, Qa, z);
	CYBOZU_BENCH_C("G2::add       ", C, G2::add, Qa, Qa, Q);
	CYBOZU_BENCH_C("G2::dbl       ", C, G2::dbl, Qa, Qa);
	CYBOZU_BENCH_C("GT::pow       ", C, GT::pow, e1, e1, a);
//	CYBOZU_BENCH_C("GT::powGLV    ", C, BN::param.glv2.pow, e1, e1, a);
	G1 PP;
	G2 QQ;
	std::string s;
	s = P.getStr();
	CYBOZU_BENCH_C("G1::setStr chk", C, PP.setStr, s);
	verifyOrderG1(false);
	CYBOZU_BENCH_C("G1::setStr    ", C, PP.setStr, s);
	verifyOrderG1(true);
	s = Q.getStr();
	CYBOZU_BENCH_C("G2::setStr chk", C, QQ.setStr, s);
	verifyOrderG2(false);
	CYBOZU_BENCH_C("G2::setStr    ", C, QQ.setStr, s);
	verifyOrderG2(true);
	CYBOZU_BENCH_C("hashAndMapToG1", C, hashAndMapToG1, PP, "abc", 3);
	CYBOZU_BENCH_C("hashAndMapToG2", C, hashAndMapToG2, QQ, "abc", 3);
#endif
	CYBOZU_BENCH_C("Fp::add       ", C3, Fp::add, x, x, y);
	CYBOZU_BENCH_C("Fp::sub       ", C3, Fp::sub, x, x, y);
	CYBOZU_BENCH_C("Fp::neg       ", C3, Fp::neg, x, x);
	CYBOZU_BENCH_C("Fp::mul       ", C3, Fp::mul, x, x, y);
	CYBOZU_BENCH_C("Fp::sqr       ", C3, Fp::sqr, x, x);
	CYBOZU_BENCH_C("Fp::inv       ", C3, Fp::inv, x, x);
	Fp2 xx, yy;
	xx.a = x;
	xx.b = 3;
	yy.a = y;
	yy.b = -5;
	CYBOZU_BENCH_C("Fp2::add      ", C3, Fp2::add, xx, xx, yy);
	CYBOZU_BENCH_C("Fp2::sub      ", C3, Fp2::sub, xx, xx, yy);
	CYBOZU_BENCH_C("Fp2::neg      ", C3, Fp2::neg, xx, xx);
	CYBOZU_BENCH_C("Fp2::mul      ", C3, Fp2::mul, xx, xx, yy);
	CYBOZU_BENCH_C("Fp2::mul_xi   ", C3, Fp2::mul_xi, xx, xx);
	CYBOZU_BENCH_C("Fp2::sqr      ", C3, Fp2::sqr, xx, xx);
	CYBOZU_BENCH_C("Fp2::inv      ", C3, Fp2::inv, xx, xx);
	FpDbl d0, d1;
	x = 9;
	y = 3;
	CYBOZU_BENCH_C("FpDbl::addPre ", C3, FpDbl::addPre, d1, d1, d0);
	CYBOZU_BENCH_C("FpDbl::subPre ", C3, FpDbl::subPre, d1, d1, d0);
	CYBOZU_BENCH_C("FpDbl::add    ", C3, FpDbl::add, d1, d1, d0);
	CYBOZU_BENCH_C("FpDbl::sub    ", C3, FpDbl::sub, d1, d1, d0);
	CYBOZU_BENCH_C("FpDbl::mulPre ", C3, FpDbl::mulPre, d0, x, y);
	CYBOZU_BENCH_C("FpDbl::sqrPre ", C3, FpDbl::sqrPre, d1, x);
	CYBOZU_BENCH_C("FpDbl::mod    ", C3, FpDbl::mod, x, d0);

	CYBOZU_BENCH_C("GT::add       ", C2, GT::add, e1, e1, e2);
	CYBOZU_BENCH_C("GT::mul       ", C2, GT::mul, e1, e1, e2);
	CYBOZU_BENCH_C("GT::sqr       ", C2, GT::sqr, e1, e1);
	CYBOZU_BENCH_C("GT::inv       ", C2, GT::inv, e1, e1);
	CYBOZU_BENCH_C("pairing       ", C, pairing, e1, P, Q);
	CYBOZU_BENCH_C("millerLoop    ", C, millerLoop, e1, P, Q);
	CYBOZU_BENCH_C("finalExp      ", C, finalExp, e1, e1);
//exit(1);
	std::vector<Fp6> Qcoeff;
	precomputeG2(Qcoeff, Q);
	CYBOZU_BENCH_C("precomputedML ", C, precomputedMillerLoop, e2, P, Qcoeff);
}
