import Login from "../components/Login"
import styles from '../styles/modules/LoginPage.module.css'

const LoginPage: React.FC = () => {
    return (
        <div className={styles.pageContainer}>
            <Login/>
        </div>
    );
};

export default LoginPage;
