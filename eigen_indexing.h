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

#include <Eigen/Dense>

// From: https://eigen.tuxfamily.org/dox-devel/TopicCustomizing_NullaryExpr.html
template<class ArgType, class RowIndexType, class ColIndexType>
class indexing_functor {
	const ArgType &m_arg;
	const RowIndexType &m_rowIndices;
	const ColIndexType &m_colIndices;
public:
	typedef Eigen::Matrix<typename ArgType::Scalar,
		RowIndexType::SizeAtCompileTime,
		ColIndexType::SizeAtCompileTime,
		ArgType::Flags&Eigen::RowMajorBit ? Eigen::RowMajor : Eigen::ColMajor,
		RowIndexType::MaxSizeAtCompileTime,
		ColIndexType::MaxSizeAtCompileTime> MatrixType;
	indexing_functor(const ArgType& arg, const RowIndexType& row_indices, const ColIndexType& col_indices)
		: m_arg(arg), m_rowIndices(row_indices), m_colIndices(col_indices)
	{}
	const typename ArgType::Scalar& operator() (Eigen::Index row, Eigen::Index col) const {
		return m_arg(m_rowIndices[row], m_colIndices[col]);
	}
};

/** An indexing(A,rows,cols) function creating the nullary expression:
  * See docs: https://eigen.tuxfamily.org/dox-devel/TopicCustomizing_NullaryExpr.html
  */
template <class ArgType, class RowIndexType, class ColIndexType>
Eigen::CwiseNullaryOp<indexing_functor<ArgType, RowIndexType, ColIndexType>, typename indexing_functor<ArgType, RowIndexType, ColIndexType>::MatrixType>
indexing(const Eigen::MatrixBase<ArgType>& arg, const RowIndexType& row_indices, const ColIndexType& col_indices)
{
	typedef indexing_functor<ArgType, RowIndexType, ColIndexType> Func;
	typedef typename Func::MatrixType MatrixType;
	return MatrixType::NullaryExpr(row_indices.size(), col_indices.size(), Func(arg.derived(), row_indices, col_indices));
}

