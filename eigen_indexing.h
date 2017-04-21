/******************************************************************************
Prácticas de cálculo matricial de estructuras
https://github.com/ingmec-ual/practicas-calculo-matricial-estructuras

Copyright 2017 - Jose Luis Blanco Claraco <jlblanco@ual.es>
University of Almeria
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.
Complete BSD-3-clause License: https://opensource.org/licenses/BSD-3-Clause
******************************************************************************/

#include <Eigen/Core>
#include <array>

template <class ArgType,class RowIndexType,class ColIndexType> class Indexing;

namespace Eigen
{
namespace internal
{
template <class ArgType,class RowIndexType,class ColIndexType>
struct traits<Indexing<ArgType,RowIndexType,ColIndexType> >
{
	typedef Eigen::Dense StorageKind;
	typedef Eigen::MatrixXpr XprKind;
	typedef typename ArgType::StorageIndex StorageIndex;
	typedef typename ArgType::Scalar Scalar;
	enum {
		Flags = Eigen::ColMajor,
		RowsAtCompileTime = std::tuple_size<RowIndexType>::value,
		ColsAtCompileTime = std::tuple_size<ColIndexType>::value,
		MaxRowsAtCompileTime = std::tuple_size<RowIndexType>::value,
		MaxColsAtCompileTime = std::tuple_size<ColIndexType>::value
	};
};
}
}

template <class ArgType,class RowIndexType,class ColIndexType>
class Indexing : public Eigen::MatrixBase<Indexing<ArgType,RowIndexType,ColIndexType> >
{
public:
	Indexing(const ArgType& arg,const RowIndexType &ri,const ColIndexType &ci)
		: m_arg(arg),m_row_indices(ri),m_col_indices(ci)
	{
		//EIGEN_STATIC_ASSERT(ArgType::ColsAtCompileTime == 1,YOU_TRIED_CALLING_A_VECTOR_METHOD_ON_A_MATRIX);
	}
	typedef typename Eigen::internal::ref_selector<Indexing>::type Nested;
	typedef Eigen::Index Index;
	Index rows() const { return std::tuple_size<RowIndexType>::value; }
	Index cols() const { return std::tuple_size<ColIndexType>::value; }
	typedef typename Eigen::internal::ref_selector<ArgType>::type ArgTypeNested;
	ArgTypeNested m_arg;
	const RowIndexType & m_row_indices;
	const ColIndexType & m_col_indices;

	template <class Derived>
	Indexing<ArgType,RowIndexType,ColIndexType> operator =(const Eigen::EigenBase<Derived>& o)
	{
		eigen_assert(this->rows()==o.rows());
		eigen_assert(this->cols()==o.cols());
		for (Index r=0;r<rows();r++) {
			for (Index c=0;c<cols();c++) {
				const_cast<ArgType&>(m_arg).coeffRef(m_row_indices[r],m_col_indices[c]) = o.derived().coeff(r,c);
			}
		}
		return *this;
	}
};

namespace Eigen
{
namespace internal
{
template<typename ArgType,class RowIndexType,class ColIndexType>
struct evaluator<Indexing<ArgType,RowIndexType,ColIndexType> >
		: evaluator_base<Indexing<ArgType,RowIndexType,ColIndexType> >
{
	typedef Indexing<ArgType,RowIndexType,ColIndexType> XprType;
	typedef typename nested_eval<ArgType, XprType::ColsAtCompileTime>::type ArgTypeNested;
	typedef typename remove_all<ArgTypeNested>::type ArgTypeNestedCleaned;
	typedef typename XprType::CoeffReturnType CoeffReturnType;
	enum {
		CoeffReadCost = evaluator<ArgTypeNestedCleaned>::CoeffReadCost,
		Flags = Eigen::ColMajor
	};

	evaluator(const XprType& xpr)
		: m_argImpl(xpr.m_arg), m_row_indices(xpr.m_row_indices),m_col_indices(xpr.m_col_indices)
	{ }
	CoeffReturnType coeff(Index row, Index col) const
	{
		return m_argImpl.coeff(m_row_indices[row],m_col_indices[col]);
	}
	evaluator<ArgTypeNestedCleaned> m_argImpl;
	const RowIndexType & m_row_indices;
	const ColIndexType & m_col_indices;
};
}
}

template <class ArgType,class RowIndexType, class ColIndexType>
Indexing<ArgType,RowIndexType,ColIndexType> indexing(const Eigen::MatrixBase<ArgType>& arg, const RowIndexType& row_indices, const ColIndexType& col_indices)
{
	return Indexing<ArgType,RowIndexType,ColIndexType>(arg.derived(),row_indices,col_indices);
}

