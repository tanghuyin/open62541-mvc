import org.dom4j.Attribute;
import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;

import java.io.File;
import java.util.*;

public class getAllNodeId {

    public static void readXML() throws Exception {
        SAXReader reader = new SAXReader();
        Document document = reader.read(new File(("C:\\Users\\17222\\Documents\\WorkSpace\\undergraduate\\62541\\project\\robot.xml")));
        Element root = document.getRootElement();
        List<Element> var = root.elements();
        Queue<String> nodeId = new LinkedList<>();
        Map<String, String> map = new HashMap<>();
        Map<String, String> nameMap = new HashMap<>();
        var.stream()
                .filter(element -> element.attributeValue("NodeId") != null)
                .forEach(element -> {
                    Element e = element.element("DisplayName");
                    nameMap.put(element.attributeValue("NodeId"), e.getText());
                });
        // get the root type
        var.stream()
                .filter(element -> element.attributeValue("BrowseName") != null && element.attributeValue("BrowseName").equals("1:RobotType"))
                .forEach(element -> {
            nodeId.add(element.attributeValue("NodeId"));
            map.put(element.attributeValue("NodeId"), "root");
        });
        while (!nodeId.isEmpty()) {
            String id = nodeId.remove();
            var.stream()
                    .filter(element -> element.attributeValue("NodeId") != null && element.attributeValue("NodeId").equals(id))
                    .forEach(element -> {
                        Element son = element.element("References");
                        List<Element> sons = son.elements("Reference");
                        sons.stream()
                                .filter(element1 -> element1.attributeValue("ReferenceType").equals("HasComponent") && element1.attributeValue("IsForward") == null)
                                .forEach(element1 -> {
                                    //System.out.println(element1.attributeValue("ReferenceType"));
                                    //System.out.println(element1.getText());
                                    nodeId.add(element1.getText());
                                    map.put(element1.getText(), id);
                                });
                    });
        }

        //var = root.elements("UAVariable");
        ArrayList<LinkedList<String>> arr = new ArrayList<>();
        var.stream()
                .filter(element -> {
                    String id = element.attributeValue("NodeId");
                    if (map.get(id) == null) return false;
                    else return true;
                })
                .forEach(element -> {
                    LinkedList<String> tmp = new LinkedList<>();

                    String father = "";
                    String id = element.attributeValue("NodeId");
                    tmp.add(nameMap.get(id));
                    while ((father=map.get(id)) != null) {
                        tmp.addFirst(nameMap.get(father));
                        id = father;
                    }
                    arr.add(tmp);
                });
//        for (LinkedList<String> list : arr) {
//            String name = "";
//            for (int i = 2; i < list.size(); i++) {
//                name += list.get(i) + "_";
//            }
//            StringBuilder sb1 = new StringBuilder();
//            sb1.append("UA_QualifiedName " + name + "nameArr" + "[" + (list.size()-1) + "] = {UA_QUALIFIEDNAME(1, \"myFirstRobot\"), ");
//            for (int i = 2; i < list.size(); i++) {
//                sb1.append("UA_QUALIFIEDNAME(2, \"" + list.get(i) + "\"), ");
//            }
//            sb1.deleteCharAt(sb1.length()-1);
//            sb1.deleteCharAt(sb1.length()-1);
//            sb1.append("};");
//            System.out.println(sb1.toString());
//
//            StringBuilder sb2 = new StringBuilder();
//            sb2.append("UA_NodeId " + name + "id;");
//            System.out.println(sb2.toString());
//
//            StringBuilder sb3 = new StringBuilder();
//            sb3.append("ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), " + (list.size()-1) + ", " + name + "nameArr, " + "&" + name + "id);");
//            System.out.println(sb3.toString());
//
//            // System.out.println("printf(\"%u \\n\", " + name + "id.identifier.numeric);");
//            System.out.println("hashmap_set(hashmap, \"" + name + "\", &" + name + "id, NULL);");
//            System.out.println();
//        }

        for (LinkedList<String> list : arr) {
            String name = "";
            for (int i = 2; i < list.size(); i++) {
                name += list.get(i) + "_";
            }
            System.out.println("static void beforeRead" + name + "Value(UA_Server *server,\n" +
                    "        const UA_NodeId *sessionId, void *sessionContext,\n" +
                    "        const UA_NodeId *nodeid, void *nodeContext,\n" +
                    "        const UA_NumericRange *range, const UA_DataValue *data) { \n" +
                    "    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, \"" + name + "Value is to be updated.\");");
            System.out.println("    updateCurrent" + name + "Value(server, *nodeid);");
            System.out.println("}");

            System.out.println("static void afterWrite" + name + "Value(UA_Server *server,\n" +
                    "        const UA_NodeId *sessionId, void *sessionContext,\n" +
                    "        const UA_NodeId *nodeid, void *nodeContext,\n" +
                    "        const UA_NumericRange *range, const UA_DataValue *data) { \n" +
                    "    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, \"" + name + "Value is modified.\");");
            System.out.println("}");

            System.out.println("static void add" + name + "CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {");
            System.out.println("    UA_ValueCallback callback;");
            System.out.println("    callback.onRead = " + "beforeRead" + name + "Value;");
            System.out.println("    callback.onWrite = " + "afterWrite" + name + "Value;");
            System.out.println("    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);");
            System.out.println("}");
        }

//        for (LinkedList<String> list : arr) {
//            String name = "";
//            for (int i = 2; i < list.size(); i++) {
//                name += list.get(i) + "_";
//            }
//            System.out.println("static void updateCurrent" + name + "Value(UA_Server *server, UA_NodeId nodeId) {");
//            System.out.println("}");
//        }

    }

    public static void main(String[] args) throws Exception {
        readXML();
    }

}
