感觉可能是他们公司有几套不同的opcua，这个ua的nodeid 62541里找不到，于是我把那段删了，好像没报啥错，不过我不清楚namespace会不会有啥影响。。client能正常找到我想要的东西。

具体找不到的是这个节点Objects/Server/Namespaces 11715

![image-20200321005543003](C:\Users\17222\AppData\Roaming\Typora\typora-user-images\image-20200321005543003.png)

以及Types/ObjectTypes/BaseObjectType/NamespaceMetaDataType 11616



![image-20200321005906696](C:\Users\17222\AppData\Roaming\Typora\typora-user-images\image-20200321005906696.png)





我想要在已经建立的变量节点上实现DataSource，但似乎无解。没有查询到相应的函数，*我不清楚如何在已经建立的变量节点上实现DataSource的方式。所以就不在这里介绍了。感觉使用回调方式已经够了。*