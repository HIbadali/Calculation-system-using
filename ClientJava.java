import java.io.*;
import java.net.Socket;

public class ClientJava {
    public static void main(String[] args) {
        try {
            // Connexion au serveur sur localhost, port 5000
            Socket socket = new Socket("127.0.0.1", 5000);
            System.out.println("Connecté au serveur.");

            // Pour envoyer des données
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            // Pour lire la réponse du serveur
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            // Envoi des 3 lignes
            out.println("NUMBER:10");
            out.println("NUMBER:5");
            out.println("OPERATOR:+");

            // Lecture de la réponse
            String response = in.readLine();
            System.out.println("Réponse du serveur : " + response);

            // Fermeture
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
