#pragma once
#ifndef PRINT_FILED_H
#define PRINT_FILED_H

#define _PRINT(a,b) printf(#a,b);
#define PRINT_FILED(a,b,c) _PRINT(a is %b \n, c)
#endif /* end of include guard: PRINT_FILED_H */

