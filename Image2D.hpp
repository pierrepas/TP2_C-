#ifndef _IMAGE2D_HPP_
#define _IMAGE2D_HPP_
#include <vector>
/// Classe générique pour représenter des images 2D.
//
template <typename TValue>
class Image2D {
    public:
        typedef Image2D<TValue>    Self;      // le type de *this
        typedef TValue             Value;     // le type pour la valeur des pixels
        typedef std::vector<Value> Container; // le type pour stocker les valeurs des pixels de l'image.

        struct Iterator : public Container::iterator {
            Iterator( Self& image, int x, int y )
                :std::vector<Value>::iterator(image.m_data.begin() + image.index(x, y)){};
        };

        struct ConstIterator : public Container::const_iterator{
            ConstIterator( const Self& image , int x, int y )
                :std::vector<Value>::const_iterator(image.m_data.begin() + image.index(x, y)){};
        };


        template <typename TAccessor>
            struct GenericConstIterator : public ConstIterator {
                typedef TAccessor Accessor;
                typedef typename Accessor::Argument  ImageValue;
                typedef typename Accessor::Value     Value;
                typedef typename Accessor::Reference Reference;

                GenericConstIterator( const Image2D<ImageValue>& image, int x, int y )
                    : ConstIterator(image, x, y){};

                Value operator*() const
                { return Accessor::access( Container::const_iterator::operator*() ); }
            };

        template <typename Accessor>
            GenericConstIterator< Accessor > start( int x=0 , int y=0  ) const
            { return GenericConstIterator< Accessor >( *this, x, y  );  }

        template <typename Accessor>
            GenericConstIterator< Accessor > begin() const
            { return start< Accessor >( 0, 0);  }

        template <typename Accessor>
            GenericConstIterator< Accessor > end() const
            { return start< Accessor >( 0, h() );  }
        template <typename TAccessor>


            struct GenericIterator : public Iterator{
                typedef TAccessor Accessor;
                typedef typename Accessor::Argument  ImageValue; // Color ou unsigned char
                typedef typename Accessor::Value     Value;      // unsigned char (pour ColorGreenAccessor)
                typedef typename Accessor::Reference Reference;  // ColorGreenReference (pour ColorGreenAccessor)
                GenericIterator(Image2D<ImageValue>& image, int x, int y )
                    :Iterator(image, x, y){};
                /*:std::vector<Value>::const_iterator(image.begin() + image.offset(x, y)){};*/
                // Accès en lecture (rvalue)
                Value operator*() const
                { return Accessor::access( Container::iterator::operator*() ); }
                Reference operator*()
                { return Accessor::access( Container::iterator::operator*() ); }
            };

        template <typename Accessor>
            GenericIterator<Accessor> start( int x, int y )
            { return GenericIterator<Accessor>(*this, x, y); }

        template <typename Accessor>
            GenericIterator<Accessor> begin()
            { return start<Accessor>(0,0); }

        template <typename Accessor>
            GenericIterator<Accessor> end()
            { return start<Accessor>(0, h()); }

        // Constructeur par défaut
        // Constructeur avec taille w x h. Remplit tout avec la valeur g
        // (par défaut celle donnée par le constructeur par défaut).
        Image2D( int w = 0, int h=0, Value g = Value() ){
            m_width = w;
            m_height = h;
            m_data.resize(w*h);
            fill(g);
        }
        // Remplit l'image avec la valeur \a g.
        void fill( TValue g ){
            for ( int i = 0; i < w(); i++ ){
                for ( int j = 0; j < h(); j++ ){
                    at( i, j ) = g;
                }
            }
        }

        /// @return la largeur de l'image.
        int w() const{
            return m_width;
        }
        /// @return la hauteur de l'image.
        int h() const{
            return m_height;
        }

        /// Accesseur read-only à la valeur d'un pixel.
        /// @return la valeur du pixel(i,j)
        Value at( int i, int j ) const{
            return m_data[ index( i, j ) ];
        }

        /// Accesseur read-write à la valeur d'un pixel.
        /// @return une référence à la valeur du pixel(i,j)
        Value& at( int i, int j ){
            return m_data[ index( i, j ) ];
        }


        /// @return un itérateur pointant sur le début de l'image
        ConstIterator begin() const { return start( 0, 0 ); }
        /// @return un itérateur pointant après la fin de l'image
        ConstIterator end()  const { return start( 0, h() ); }
        /// @return un itérateur pointant sur le pixel (x,y).
        ConstIterator start( int x, int y ) const { return ConstIterator( *this, x, y ); }

        /// @return un itérateur pointant sur le début de l'image
        Iterator begin() { return start( 0, 0 ); }
        /// @return un itérateur pointant après la fin de l'image
        Iterator end()   { return start( 0, h() ); }
        /// @return un itérateur pointant sur le pixel (x,y).
        Iterator start( int x, int y ) { return Iterator( *this, x, y ); }


    private:
        Container m_data; // mes données; évitera de faire les allocations dynamiques
        int m_width; // ma largeur
        int m_height; // ma hauteur

        /// @return l'index du pixel (x,y) dans le tableau \red m_data.
        int index( int i, int j ) const{
            return i + w() * j;
        }
};

#endif // _IMAGE2D_HPP_
