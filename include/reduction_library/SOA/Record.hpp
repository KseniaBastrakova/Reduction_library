/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <tuple>
#include "reduction_library/record/Concept.hpp"
#include "reduction_library/helpers/Type_list.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/helpers/Tuple_idx_getters.hpp"

namespace reduction_library{
namespace SOA{

/** @file
 *
 * Implementation Record concept (reduction_library/component/Record.hpp)
 * for "SOA" data representation.
 * Represent each "record" -- data structure, that represent physical
 * Quantity for particle_species (for example: all charges, all positions, etc.)
 * stored as collection of arrays
 *
 *  define all nessary functions:
 *  provide access to each component in record by name,
 *
 *  getting all attributes: unit dimension,
 *
 *  macroweighted (indicates whether this quantity is written for the underlying particle (macroWeighted = 0),
 *  or for the full macroparticle (macroWeighted = 1)),
 *
 *  weighting power (indicates with which power of weighting (see below)
 *  the quantity should be multiplied, in order to go from the individual-particle
 *  representation to the full-macroparticle representation)
 *
 * Parameterized by T_Names_List -- collection of component's names,
 * that define in reduction_library/component/Name.hpp
 * and by T_Component_Type_List -- collection of component's objects
 */

/** Base structure for Record type
 *
 *  represent Record concept for structure of arrays data storage
 *  represent Record as set of Components objects and corresponding components
 *  names
 *
 * \tparam T_Names_List type list of component's names
 * \tparam T_Names_List type list of component's types
 */
template<typename T_Names_List, typename T_Component_Type_List>
struct Record{
public:
    //-----------------------------------------------------------------------------
    //! Type of current record
    using This = Record<T_Names_List, T_Component_Type_List>;
    //-----------------------------------------------------------------------------
    //! Type of set component's objects
    using Components = T_Component_Type_List;
    //-----------------------------------------------------------------------------
    //! Type of set component's names
    using Names = T_Names_List;
private:
    /** indicates with which power of weighting (see below) the quantity
     * should be multiplied, in order to go from the individual-particle
     *  representation to the full-macroparticle representation  */
    double weighting_power;
    /** indicates whether this quantity is
     *  written for the underlying particle or the full macroparticle  */
    int macro_weighted;
    //-----------------------------------------------------------------------------
    //! Set of component's names
    Names names;
    //-----------------------------------------------------------------------------
    //! Set of components names
    Components components;
    /** powers of the 7 base measures characterizing the record's unit
     * in SI (length L, mass M, time T, electric current I, thermodynamic
     * temperature theta, amount of substance N, luminous intensity J)  */
    record::unit_dimension_type unit_dimension;
public:
    Record(const Record& record):
        components(record.get_components()),
        macro_weighted(record.get_macro_weighted()),
        weighting_power(record.get_weighting_power()),
        unit_dimension(record.get_unit_dimension()){}

    template<typename T_Another_Names_List, typename T_Another_Component_Type_List>
    Record(const Record<T_Another_Names_List, T_Another_Component_Type_List>& record):
        components(record.get_components()),
        macro_weighted(record.get_macro_weighted()),
        weighting_power(record.get_weighting_power()),
        unit_dimension(record.get_unit_dimension()){}
    //-----------------------------------------------------------------------------
    //! Produces Record by list of components
    Record(T_Component_Type_List components):
        components(components),
        macro_weighted(7),
        weighting_power(42.),
        unit_dimension(unit_dimension){}

    //-----------------------------------------------------------------------------
    //! Returns weighting power attribute
    double get_weighting_power() const
    {
        return weighting_power;
    }
    //-----------------------------------------------------------------------------
    //! Returns macro weighted attribute
    int get_macro_weighted() const
    {
        return weighting_power;
    }
    //-----------------------------------------------------------------------------
    //! Returns unit dimension attribute
    record::unit_dimension_type get_unit_dimension() const
    {
        return unit_dimension;
    }
    //-----------------------------------------------------------------------------
    //! Returns set of components
    const Components& get_components() const
    {
        return components;
    }
    //-----------------------------------------------------------------------------
    //! Returns number of values in each component
    std::size_t get_size()
    {
        auto component = std::get< 0 >( components );
        return component.get_size();
    }
};

} //namespace SOA


namespace record{
namespace traits{
    /** Derive a type of component in Record's set by component name
     *
     *  Returns component type
     *
     * \tparam T_Component_Name -- name of requested component
     * \tparam T_Names_List -- list of all componenent's names in Record
     * \tparam T_Names_List -- list of all componenent's types in Record
     */
    template<class T_Component_Name, typename T_Names_List, typename T_Component_Type_List>
    struct Type<T_Component_Name, SOA::Record<T_Names_List, T_Component_Type_List>>
    {
        using Record = SOA::Record<T_Names_List, T_Component_Type_List>;
        using Names = typename Record::Names;
        using Components = typename Record::Components;

        using type = typename std::tuple_element_t<
                helpers::Index<T_Component_Name, Names>::value,
                Components
               >;
    };
} //namespace traits

    /** Derive a type of Record with single component
     * (scalar record)
     *
     *  Returns record type
     *
     * \tparam T_Component_Type -- type of component in Record
     */
    template<typename T_Component_Type>
    using Record_scalar = SOA::Record<helpers::Type_list<component::name::SCALAR >, helpers::Type_list<T_Component_Type>>;

    /** Derive a type of Record with three components with
     *  names X, Y, Z
     *  (3-d record)
     *
     *  Returns record type
     *
     * \tparam T_X_Component -- type of x-component
     * \tparam T_Y_Component -- type of y-component
     * \tparam T_Z_Component -- type of z-component
     */
    template<typename T_X_Component, typename T_Y_Component, typename T_Z_Component>
    using Record_XYZ = SOA::Record<helpers::Type_list<component::name::X, component::name::Y, component::name::Z>,
            helpers::Type_list<T_X_Component, T_Y_Component, T_Z_Component>>;

    /** Derive a type of Record with two components with
     *  names X, Y
     *  (2-d record)
     *
     *  Returns record type
     *
     * \tparam T_X_Component -- type of x-component
     * \tparam T_Y_Component -- type of y-component
     */
    template<typename T_X_Component, typename T_Y_Component>
    using Record_XY = SOA::Record<helpers::Type_list<component::name::X, component::name::Y>,
            helpers::Type_list<T_X_Component, T_Y_Component>>;


    /** Getting Component from given Record by name
     *
     *  Returns component object
     *
     * \tparam T_Names_List -- list of all componenent's names in input Record
     * \tparam T_Names_List -- list of all componenent's types in input Record
     * \tparam record --object of SOA::Record
     */
    template<class T_Component_name, typename T_Names_List, typename T_Component_Type_List>
    struct Getting_value<T_Component_name, SOA::Record<T_Names_List, T_Component_Type_List>>
    {
    public:
        typename traits::Type<T_Component_name, SOA::Record<T_Names_List, T_Component_Type_List>>::type &
            operator() (SOA::Record<T_Names_List, T_Component_Type_List>& record)
        {
            using Record = SOA::Record<T_Names_List, T_Component_Type_List>;
            using Names = typename Record::Names;
            constexpr auto idx = helpers::Index<T_Component_name, Names>::value;
            return std::get< idx >(record.get_components());
        }

    };

    /** Getting weighting power attribute from given Record
     *
     *  Returns weighting power
     *
     * \tparam T_Names_List -- list of all componenent's names in input Record
     * \tparam T_Names_List -- list of all componenent's types in input Record
     * \tparam record --object of SOA::Record
     */
    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_weighting_power<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      double operator() (SOA::Record<T_Names_list, T_Component_type_list>& record)
      {
          return record.get_weighting_power();
      }

    };

    /** Getting macro weighted attribute from given Record
     *
     *  Returns macro weighted
     *
     * \tparam T_Names_List -- list of all componenent's names in input Record
     * \tparam T_Names_List -- list of all componenent's types in input Record
     * \tparam record --object of SOA::Record
     */
    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_macro_weighted<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      double operator() (SOA::Record<T_Names_list, T_Component_type_list>&& record)
      {
          return record.get_macro_weighted();
      }

    };

    /** Getting unit dimension attribute from given Record
     *
     *  Returns unit dimension
     *
     * \tparam T_Names_List -- list of all componenent's names in input Record
     * \tparam T_Names_List -- list of all componenent's types in input Record
     * \tparam record --object of SOA::Record
     */
    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_unit_dimension<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      unit_dimension_type operator() (SOA::Record<T_Names_list, T_Component_type_list>& record)
      {
          return record.get_unit_dimension();
      }
    };

    /** Making record by set of components and set of components's names
     *
     *  Returns resulted record
     *
     * \tparam T_Names -- input set of names, that will compose Record
     * \tparam T_Component_Types -- set of all component's types, that will compose Record
     * \tparam components -- set of all components, that will compose Record
     */
    template<typename ... T_Names, typename ... T_Component_Types>
    auto make_record(T_Component_Types& ...  components)
    {
        using Names = helpers::Type_list< T_Names ... >;
        using Component_types = helpers::Type_list<T_Component_Types ... >;
        using Record = SOA::Record< Names, Component_types>;
        Component_types input_components(components...);
        Record record(input_components);
        return record;
    }

    /** Making scalar record by one component
     *
     *  Returns resulted record
     *
     * \tparam T_Scalar_Component -- set of all component's types, that will compose Record
     * \tparam components -- set of all components, that will compose Record
     */
    template<class T_Scalar_Component>
    Record_scalar<T_Scalar_Component> make_record_scalar(T_Scalar_Component scalar_component)
    {
        auto scalar_record = make_record<component::name::SCALAR>(scalar_component);
        return scalar_record;
    }

    /** Making 3d record by three components,
     *  with names X, Y, Z
     *
     *  Returns resulted record
     *
     * \tparam T_X_Component -- type of x-component
     * \tparam T_Y_Component -- type of y-component
     * \tparam T_Z_Component -- type of z-component
     *
     */
    template<class T_X_Component, class T_Y_Component, class T_Z_Component>
    Record_XYZ<T_X_Component, T_Y_Component, T_Z_Component> make_record_XYZ(T_X_Component x_component,
                                                                            T_Y_Component y_component,
                                                                            T_Z_Component z_component)
    {
        auto result_3d_record = make_record<component::name::X,
                component::name::Y, component::name::Z>(x_component, y_component, z_component);
        return result_3d_record;
    }

    /** Making 2d record by two components,
     *  with names X, Y
     *
     *  Returns resulted record
     *
     * \tparam T_X_Component -- type of x-component
     * \tparam T_Y_Component -- type of y-component
     *
     */

    template<class T_X_Component, class T_Y_Component>
    Record_XY<T_X_Component, T_Y_Component> make_record_XY(T_X_Component x_component,
                                                           T_Y_Component y_component)
    {
        auto result_2d_record = make_record<component::name::X,
                component::name::Y>(x_component, y_component);
        return result_2d_record;
    }

} // namespace record
}// reduction_library

