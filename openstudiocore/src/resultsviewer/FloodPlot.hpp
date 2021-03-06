/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2017, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#ifndef RESULTSVIEWER_FLOODPLOT_HPP
#define RESULTSVIEWER_FLOODPLOT_HPP

#include "../utilities/data/TimeSeries.hpp"
#include "../utilities/data/Vector.hpp"
#include "../utilities/data/Matrix.hpp"

#include <QWidget>
#include <QPushButton>
#include <QAction>

#include <qwt/qwt_plot.h>
#include <qwt/qwt_text.h>
#include <qwt/qwt_color_map.h>
#include <qwt/qwt_plot_spectrogram.h>
#include <qwt/qwt_scale_draw.h>
#include <qwt/qwt_plot_zoomer.h>
#include <qwt/qwt_plot_layout.h>

namespace openstudio{

  /** FloodPlotColorMap is class for colormap that can be used in a flood plot.
  *   \deprecated { Qwt drawing widgets are deprecated in favor of Javascript }
  */
  class  FloodPlotColorMap: public QwtLinearColorMap
  {
    public:

      /// available color maps
      enum ColorMapList {Gray, Jet};

      /// constructor
      FloodPlotColorMap(const Vector& colorLevels, ColorMapList colorMap);

      /// virtual destructor
      virtual ~FloodPlotColorMap();

    private:
      // Disabled copy constructor and operator=
      FloodPlotColorMap(const FloodPlotColorMap &);
      FloodPlotColorMap &operator=(const FloodPlotColorMap &);

      Vector m_colorLevels;
      ColorMapList m_colorMapList;
      void init();
  };


  /** FloodPlotData is abstract class for data that can be used in a flood plot.
   *  Derive from this class to plot your data.
   *  \deprecated { Qwt drawing widgets are deprecated in favor of Javascript }
   */
  class  FloodPlotData: public QwtRasterData
  {
    public:

      /// virtual destructor
      virtual ~FloodPlotData();

      /// must provide copy
      virtual FloodPlotData* copy() const = 0;

      /// must provide range of values - colormap range not data range
      //QwtInterval range() const = 0;

      // color map range
      virtual void colorMapRange(QwtInterval colorMapRange) = 0;

      /// color map range
      virtual QwtInterval colorMapRange() = 0;


      /// get the value at point x, y
      virtual double value(double x, double y) const = 0;

      /// minX
      virtual double minX() const = 0;

      /// maxX
      virtual double maxX() const = 0;

      /// minY
      virtual double minY() const = 0;

      /// maxY
      virtual double maxY() const = 0;

      /// minValue getter
      virtual double minValue() const = 0;

      /// maxValue getter
      virtual double maxValue() const = 0;

      /// minValue setter
      virtual void minValue(double min) = 0;

      /// maxValue setter
      virtual void maxValue(double max) = 0;

      /// sumValue
      virtual double sumValue() const = 0;

      /// meanValue
      virtual double meanValue() const = 0;

      /// stdDevValue
      virtual double stdDevValue() const = 0;

      /// units for plotting on axes or scaling
      virtual std::string units() const = 0;

    protected:

      FloodPlotData();
  };

  /** TimeSeriesFloodPlotData converts a time series into flood plot data
  *   \deprecated { Qwt drawing widgets are deprecated in favor of Javascript }
  */
  class  TimeSeriesFloodPlotData: public FloodPlotData
  {
    public:

      /// constructor
      TimeSeriesFloodPlotData(TimeSeries timeSeries);

      /// constructor with colormap range
      TimeSeriesFloodPlotData(TimeSeries timeSeries, QwtInterval colorMapRange );

      /// virtual destructor
      virtual ~TimeSeriesFloodPlotData();

      /// must provide copy
      virtual TimeSeriesFloodPlotData* copy() const override;

      /// must provide range of values - colormap range not data range
      QwtInterval range() const;

      /// provide boundingRect overload for speed - default implementation slow!!!
      QRectF boundingRect() const;

      /// provide size of each pixel
      virtual QRectF pixelHint(const QRectF& area) const override;

      ///  value at point fractionalDay and hourOfDay
      double value(double fractionalDay, double hourOfDay) const override;

      /// minX
      double minX() const override;

      /// maxX
      double maxX() const override;

      /// minY
      double minY() const override;

      /// maxY
      double maxY() const override;

      /// minValue
      double minValue() const override;

      /// maxValue
      double maxValue() const override;

      /// minValue setter
      void minValue(double min) override;

      /// maxValue setter
      void maxValue(double max) override;

      /// sumValue
      double sumValue() const override;

      /// meanValue
      double meanValue() const override;

      /// stdDevValue
      double stdDevValue() const override;

      /// range of values for which to show the colormap
      void colorMapRange(QwtInterval colorMapRange) override;

      /// range of values for which to show the colormap
      QwtInterval colorMapRange() override;

      /// units for plotting on axes or scaling
      std::string units() const override;

    private:
      TimeSeries m_timeSeries;
      double m_minValue;
      double m_maxValue;
      double m_minX;
      double m_maxX;
      double m_minY;
      double m_maxY;
      double m_startFractionalDay;
      QwtInterval m_colorMapRange;
      std::string m_units;
  };

  /** MatrixFloodPlotData converts a Matrix into flood plot data
  *   \deprecated { Qwt drawing widgets are deprecated in favor of Javascript }
  */
  class  MatrixFloodPlotData: public FloodPlotData
  {
    public:

      /// constructor
      MatrixFloodPlotData(const Matrix& matrix);

      /// constructor and color map range
      MatrixFloodPlotData(const Matrix& matrix, QwtInterval colorMapRange );

      /// constructor with x and y vectors
      MatrixFloodPlotData(const Vector& xVector,
          const Vector& yVector,
          const Matrix& matrix);

      /// constructor with x and y vectors and interpolation method
      MatrixFloodPlotData(const Vector& xVector,
          const Vector& yVector,
          const Matrix& matrix,
          const InterpMethod interp);

      /// constructor with x and y vectors
      MatrixFloodPlotData(const std::vector<double>& xVector,
          const std::vector<double>& yVector,
          const std::vector<double>& matrix);

      /// constructor with x and y vectors and interpolation method
      MatrixFloodPlotData(const std::vector<double>& xVector,
          const std::vector<double>& yVector,
          const std::vector<double>& matrix,
          const InterpMethod interp);

      /// constructor with x and y vectors and color map range
      MatrixFloodPlotData(const Vector& xVector,
          const Vector& yVector,
          const Matrix& matrix,
          QwtInterval colorMapRange );

      /// virtual destructor
      virtual ~MatrixFloodPlotData();

      /// must provide copy
      virtual MatrixFloodPlotData* copy() const override;

      /// must provide range of values - colormap range not data range
      QwtInterval range() const;

      /// provide size of each pixel
      virtual QRectF pixelHint(const QRectF& area) const override;

      /// get the value at point x, y
      double value(double x, double y) const override;

      /// set the interp method, defaults to Nearest
      void interpMethod(InterpMethod interpMethod);

      /// minX
      double minX() const override;

      /// maxX
      double maxX() const override;

      /// minY
      double minY() const override;

      /// maxY
      double maxY() const override;

      /// minValue
      double minValue() const override;

      /// maxValue
      double maxValue() const override;

      /// minValue setter
      void minValue(double min) override;

      /// maxValue setter
      void maxValue(double max) override;

      /// sumValue
      double sumValue() const override;

      /// meanValue
      double meanValue() const override;

      /// stdDevValue
      double stdDevValue() const override;

      /// range of values for which to show the colormap
      void colorMapRange(QwtInterval colorMapRange) override;

      /// range of values for which to show the colormap
      QwtInterval colorMapRange() override;

      /// units for plotting on axes or scaling
      std::string units() const override;

    private:

      // set ranges and bounding box
      void init();
      double m_minValue;
      double m_maxValue;
      Vector m_xVector;
      Vector m_yVector;
      Matrix m_matrix;
      InterpMethod m_interpMethod;
      double m_minX, m_maxX, m_minY, m_maxY;
      QwtInterval m_colorMapRange;
      Vector m_colorMapScaleValues;
      std::string m_units;
  };

} // openstudio

#endif // RESULTSVIEWER_FLOODPLOT_HPP
