
/*
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email ferdinando@ametrano.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
/*! \file riskstatisticss.hpp
    \brief Normal distribution risk analysis tool: VAR, (average) shortfall

    \fullpath
    ql/%riskstatisticss.hpp
*/

// $Id$

#ifndef quantlib_risk_statisticss_h
#define quantlib_risk_statisticss_h

#include <ql/Math/statistics.hpp>
#include <ql/Math/riskmeasures.hpp>

namespace QuantLib {

    //! Risk analysis tool
    /*! It can accumulate a set of data and return risk quantities
        as Value-At-Risk, Expected Shortfall,
        Shortfall, Average Shortfall, plus statistics
        quantitities as mean, variance, std. deviation, skewness, kurtosis.

        \deprecated use Statistics instead (or even take a look at
                    HStatisticss)
    */
    class RiskStatisticss {
      public:
        //! \name Inspectors
        //@{
        // Statistics proxy methods
        Size samples() const {return statistics_.samples(); }
        double weightSum() const {return statistics_.weightSum(); }
        double mean() const {return statistics_.mean(); }
        double variance() const {return statistics_.variance(); }
        double standardDeviation() const {
            return statistics_.standardDeviation(); }
        double errorEstimate() const {
            return statistics_.errorEstimate(); }
        double skewness() const {return statistics_.skewness(); }
        double kurtosis() const {return statistics_.kurtosis(); }
        double min() const {return statistics_.min(); }
        double max() const {return statistics_.max(); }

        // RiskMeasures proxy methods
        //! returns the Potential-Upside at a given percentile
        double potentialUpside(double percentile) const {
            return riskMeasures_.potentialUpside(percentile,
                statistics_.mean(), statistics_.standardDeviation());
        }
        //! returns the Value-At-Risk at a given percentile
        double valueAtRisk(double percentile) const {
            return riskMeasures_.valueAtRisk(percentile,
                statistics_.mean(), statistics_.standardDeviation());
        }
        //! returns the Expected Shortfall at a given percentile
        double expectedShortfall(double percentile) const {
            return riskMeasures_.expectedShortfall(percentile,
                statistics_.mean(), statistics_.standardDeviation());
        }
        //! returns the Shortfall (observations below target)
        double shortfall(double target) const {
            return riskMeasures_.shortfall(target,
                statistics_.mean(), statistics_.standardDeviation());
        }
        //! returns the Average Shortfall (averaged shortfallness)
        double averageShortfall(double target) const  {
            return riskMeasures_.averageShortfall(target,
                statistics_.mean(), statistics_.standardDeviation());
        }
        //@}
        //! \name Modifiers
        //@{
        void add(double value, double weight = 1.0);
        template <class DataIterator>
        void addSequence(DataIterator begin, DataIterator end) {
          for (;begin!=end;++begin)
            add(*begin);
        }
        //! adds a sequence of data to the set, each with its weight
        template <class DataIterator, class WeightIterator>
        void addSequence(DataIterator begin, DataIterator end,
          WeightIterator wbegin) {
            for (;begin!=end;++begin,++wbegin)
                add(*begin, *wbegin);
        }
        void reset();

        //@}
      private:
        Math::Statistics statistics_;
        Math::RiskMeasures riskMeasures_;
    };

    // inline definitions

    /*! \pre weights must be positive or null */
    inline void RiskStatisticss::add(double value, double weight) {
        statistics_.add( value , weight );
    }

    inline void RiskStatisticss::reset() {
        statistics_.reset();
    }

}


#endif
