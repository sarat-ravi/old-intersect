import xml.sax
import xml.sax.saxutils
import xml.sax.handler
import string
filename = "swig_test_wrap.xml"

class docHandler(xml.sax.ContentHandler):
    pass

class Function:
    def __init__(self):
        self.__name = None
        self.__arguments = []
        self.__return_type = None

    def _GetType(self, name):
        """
        
        """
        tmp = string.split(name, '.')
        l = len(tmp)
        if l == 2:
            return tmp[1]
        elif l == 1:
            return tmp[0]
        else:
            raise ValueError, "Unknown length l = %d" % (l,)

    def _IsPointer(self, name):
        if name[:2] == "p.":
            return True
        return False
    
    def SetName(self, name):
        self.__name = name

    def AddArgument(self, name):
        mytype = self._GetType(name)
        if self._IsPointer(name):
            mytype = "*" + mytype
        self.__arguments.append(mytype)

    def SetReturnType(self, t):
        self.__return_type = t
        
    def __str__(self):
        args = string.join(self.__arguments, ", ")
        return "%s\t %s(%s);" %(self.__return_type, self.__name,args)
        
class FindFunction(xml.sax.saxutils.DefaultHandler):
    __cdecl = "cdecl"
    def __init__(self):
        xml.sax.saxutils.DefaultHandler.__init__(self)
        self.__in_function = 0
        self.__the_function = None
        self.__in_parm = 0
        
    def startElement(self, name, attrs):
        if name == self.__cdecl:
            assert(self.__in_function == 0)
            self.__in_function = 1
            self.__the_function = Function()

        elif name == "parm" and self.__in_function == 1:
            self.__in_parm = 1

        if self.__in_function:
            try:
                aname = attrs["name"]
            except KeyError:
                return

            if self.__in_parm:
                if aname == "type":
                    self.__the_function.AddArgument(attrs["value" ])
            else:        
                if aname == "type":
                    self.__the_function.SetReturnType(attrs["value" ])
                    
                if aname  == "decl":
                    testfunction = attrs["value"]
                    if testfunction[:2] == "f(":
                        pass
                        #print testfunction
                    else:
                        self.__in_function = 0
                        self.__the_function = None

                elif aname  == "sym_name":
                    self.__the_function.SetName(attrs["value"])


                
                
    def endElement(self, name):
        if name == self.__cdecl:
            self.__in_function = 0
            print self.__the_function
            
        elif name == "parm":
            self.__in_parm = 0
    
def test():
    #reader = xml.sax.xmlreader.XMLReader()
    #xml.sax.parse(open(filename), xml.sax.ContentHandler)
    parser = xml.sax.make_parser()
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)

    dh = FindFunction()
    parser.setContentHandler(dh)
    parser.parse(open(filename))
    pass

if __name__ == '__main__':
    test()
