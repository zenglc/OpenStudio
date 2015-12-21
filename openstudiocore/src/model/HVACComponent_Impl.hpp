/**********************************************************************
 *  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/
#ifndef MODEL_HVACCOMPONENT_IMPL_HPP
#define MODEL_HVACCOMPONENT_IMPL_HPP


#include "ParentObject_Impl.hpp"
#include "AirLoopHVAC.hpp"
#include "AirLoopHVACOutdoorAirSystem.hpp"
#include "PlantLoop.hpp"

namespace openstudio {

namespace model {

class Node;

class Splitter;

class ZoneHVACComponent;

namespace detail {

class MODEL_API HVACComponent_Impl : public ParentObject_Impl {
  Q_OBJECT;

  Q_PROPERTY(bool isRemovable READ isRemovable);
  Q_PROPERTY(boost::optional<openstudio::model::ModelObject> airLoopHVAC READ airLoopHVACAsModelObject);
  Q_PROPERTY(boost::optional<openstudio::model::ModelObject> plantLoop READ plantLoopAsModelObject);
  Q_PROPERTY(boost::optional<openstudio::model::ModelObject> airLoopHVACOutdoorAirSystem READ airLoopHVACOutdoorAirSystemAsModelObject);

 public:

  HVACComponent_Impl( IddObjectType type, Model_Impl* model);

  HVACComponent_Impl( const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

  HVACComponent_Impl( const openstudio::detail::WorkspaceObject_Impl& other,
                      Model_Impl* model,
                      bool keepHandle );

  HVACComponent_Impl( const HVACComponent_Impl& other, Model_Impl* model, bool keepHandles );

  virtual ~HVACComponent_Impl() {}

  virtual boost::optional<AirLoopHVAC> airLoopHVAC() const;

  virtual boost::optional<PlantLoop> plantLoop() const;

  virtual boost::optional<Loop> loop() const;

  virtual boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

  virtual bool addToNode(Node & node);

  virtual bool addToSplitter(Splitter & splitter);

  virtual boost::optional<ParentObject> parent() const override;

  virtual std::vector<ModelObject> children() const override;

  virtual const std::vector<std::string>& outputVariableNames() const override;

  virtual void disconnect();

  virtual std::vector<IdfObject> remove() override;

  virtual bool isRemovable() const;

  virtual ModelObject clone(Model model) const override;

  /** This function returns a vector of HVACComponent that are directly downstream
   *  from this object on an AirLoopHVAC or PlantLoop. 
   *  @param[in] previous is used to indicate which path of edges to return 
  **/
  virtual std::vector<HVACComponent> edges(const boost::optional<HVACComponent> & previous);

  virtual boost::optional<HVACComponent> containingHVACComponent() const;

  virtual boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const;
  
  virtual boost::optional<StraightComponent> containingStraightComponent() const;

  bool addToNode(Node & node, 
    const HVACComponent & systemStartComponent, 
    const HVACComponent & systemEndComponent,
    unsigned componentInletPort,
    unsigned componentOutletPort);

  bool removeFromLoop( const HVACComponent & systemStartComponent, 
    const HVACComponent & systemEndComponent,
    unsigned componentInletPort,
    unsigned componentOutletPort );

 protected:

  friend class Model_Impl;

  mutable boost::optional<AirLoopHVAC> m_airLoopHVAC;
  mutable boost::optional<PlantLoop> m_plantLoop;
  mutable boost::optional<AirLoopHVACOutdoorAirSystem> m_airLoopHVACOutdoorAirSystem;

 private:

  REGISTER_LOGGER("openstudio.model.HVACComponent");

  boost::optional<ModelObject> airLoopHVACAsModelObject() const;
  boost::optional<ModelObject> plantLoopAsModelObject() const;
  boost::optional<ModelObject> airLoopHVACOutdoorAirSystemAsModelObject() const;
};

} // detail

} // model
} // openstudio

#endif
