#ifndef PLOT_HPP
#define PLOT_HPP

#ifdef SCIPLOT
   #include "sciplot/sciplot.hpp"
#endif

// for the moment I will just do it this way but on the long run I should wrap sciplot library with my own plotting interface to avoid to much coupling


namespace plt = sciplot;

//namespace plt {
//namespace tags
//{
//    struct sciplot{};
//}
//}// plot


#endif // PLOT_HPP
