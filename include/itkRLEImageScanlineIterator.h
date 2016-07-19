/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef itkRLEImageScanlineIterator_h
#define itkRLEImageScanlineIterator_h

#include "itkRLEImageScanlineConstIterator.h"
#include "itkRLEImageIterator.h"
#include "itkImageScanlineIterator.h"

namespace itk
{
/** \class ImageScanlineIterator
*  \brief A multi-dimensional iterator templated over image type that
*  walks a region of pixels, scanline by scanline or in the direction
*  of the fastest axis. Read-write access. Specialized for RLEImage.
*  \ingroup RLEImage
*  \ingroup ITKCommon
*/
template< typename TPixel, unsigned int VImageDimension, typename CounterType >
class ImageScanlineIterator<RLEImage<TPixel, VImageDimension, CounterType> >
    :public ImageScanlineConstIterator<RLEImage<TPixel, VImageDimension, CounterType> >
{
public:
    /** Standard class typedefs. */
    typedef ImageScanlineIterator                Self;
    typedef ImageScanlineConstIterator<RLEImage<TPixel, VImageDimension, CounterType> > Superclass;

    /** Types inherited from the Superclass */
    typedef typename Superclass::IndexType             IndexType;
    typedef typename Superclass::SizeType              SizeType;
    typedef typename Superclass::OffsetType            OffsetType;
    typedef typename Superclass::RegionType            RegionType;
    typedef typename Superclass::ImageType             ImageType;
    typedef typename Superclass::InternalPixelType     InternalPixelType;
    typedef typename Superclass::PixelType             PixelType;

    /** Default constructor. Needed since we provide a cast constructor. */
    ImageScanlineIterator()
        :ImageScanlineConstIterator< ImageType >() {}

    /** Constructor establishes an iterator to walk a particular image and a
    * particular region of that image. */
    ImageScanlineIterator(ImageType *ptr, const RegionType & region)
        :ImageScanlineConstIterator< ImageType >(ptr, region) {}

    /** Constructor that can be used to cast from an ImageIterator to an
    * ImageScanlineIterator. Many routines return an ImageIterator but for a
    * particular task, you may want an ImageScanlineIterator.  Rather than
    * provide overloaded APIs that return different types of Iterators, itk
    * returns ImageIterators and uses constructors to cast from an
    * ImageIterator to a ImageScanlineIterator. */
    ImageScanlineIterator(const ImageIterator< ImageType > & it)
        :ImageScanlineConstIterator< ImageType >(it) {}

    /** Set the pixel value */
    void Set(const PixelType & value) const
    {
        const_cast<ImageType *>(this->m_Image.GetPointer())->
            SetPixel(*const_cast<typename ImageType::RLLine *>(this->rlLine),
            this->segmentRemainder, this->realIndex, value);
    }

    ///** Return a reference to the pixel
    //* This method will provide the fastest access to pixel
    //* data, but it will NOT support ImageAdaptors. */
    //PixelType & Value(void)
    //{
    //    return m_Buffer[m_Index[2]][m_Index[1]][realIndex].second;
    //}

protected:
    /** the construction from a const iterator is declared protected
    in order to enforce const correctness. */
    ImageScanlineIterator(const ImageScanlineConstIterator< ImageType > & it)
        :ImageScanlineConstIterator< ImageType >(it) {}
    Self & operator=(const ImageScanlineConstIterator< ImageType > & it)
    {
        this->ImageScanlineConstIterator< ImageType >::operator=(it);
        return *this;
    }
};
} // end namespace itk

#endif //itkRLEImageScanlineIterator_h