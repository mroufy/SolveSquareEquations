void run_tests()
{
    int tests_completed = 0;
    const int tests_num = 7;

    tests_completed += run_one_test(1, 0, 0, ONE_ROOT, 0, NAN);
    tests_completed += run_one_test(0, 1, 0, ONE_ROOT, 0, NAN);
    tests_completed += run_one_test(0, 0, 1, NO_ROOTS, NAN, NAN);
    tests_completed += run_one_test(0, 0, 0, INF_ROOTS, NAN, NAN);
    tests_completed += run_one_test(1, -2, 1, ONE_ROOT, 1, NAN);
    tests_completed += run_one_test(1, -5, 6, TWO_ROOTS, 2, 3);
    tests_completed += run_one_test(1, -13, 42, TWO_ROOTS, 6, 7);

    if (tests_completed == tests_num)
        printf("%sAll test completed %d/%d\n%s", C_GREEN, tests_completed, tests_num, C_RESET);
    else
        printf("%sTests completed %d/%d\n%s", C_YELLOW, tests_completed, tests_num, C_RESET);
}


int run_one_test(double a, double b, double c, int root_num_ref, double x_1ref, double x_2ref)
{
    double x_1 = NAN, x_2 = NAN;
    int root_num = solve_square_equation(a, b, c, &x_1, &x_2);

    x_1 = remove_minus_zero(x_1);
    x_2 = remove_minus_zero(x_2);

    if (root_num != root_num_ref || !(compare_double(x_1, x_1ref)) || !(compare_double(x_2, x_2ref)))
    {
        printf("%sTest FAILED: a = %lg, b = %lg, c = %lg\nExpected %d roots, x_1 = %lg, x_2 = %lg\nGot %d roots, x_1 = %lg, x_2 = %lg\n%s", C_RED, a, b, c, root_num_ref, x_1ref, x_2ref, root_num, x_1, x_2, C_RESET);
        return 0;
    }
    else
        return 1;
}
