package main

import (
	"context"
	"flag"
	"fmt"
	"path/filepath"

	corev1 "k8s.io/api/core/v1"
	"k8s.io/apimachinery/pkg/api/errors"
	metav1 "k8s.io/apimachinery/pkg/apis/meta/v1"
	"k8s.io/client-go/kubernetes"
	_ "k8s.io/client-go/plugin/pkg/client/auth"
	"k8s.io/client-go/tools/clientcmd"
	"k8s.io/client-go/util/homedir"
)

func main() {
	var kubeconfig *string
	if home := homedir.HomeDir(); home != "" {
		kubeconfig = flag.String("kubeconfig", filepath.Join(home, ".kube", "config"), "(optional) absolute path to the kubeconfig file")
	} else {
		kubeconfig = flag.String("kubeconfig", "", "absolute path to the kubeconfig file")
	}
	podFlag := flag.Bool("pod", false, "show pod name")
	svcFlag := flag.Bool("svc", false, "show service name")
	deployFlag := flag.Bool("deploy", false, "show deployment name")
	ingFlag := flag.Bool("ingress", false, "show ingress name")
	cmFlag := flag.Bool("cm", false, "show configmap name")
	flag.Parse()
	config, err := clientcmd.BuildConfigFromFlags("", *kubeconfig)
	if err != nil {
		panic(err.Error())
	}
	clientset, err := kubernetes.NewForConfig(config)
	if err != nil {
		panic(err.Error())
	}

	namespace := corev1.NamespaceDefault

	if *podFlag {
		pods, err := clientset.CoreV1().Pods(namespace).List(context.TODO(), metav1.ListOptions{})
		if err != nil {
			panic(err.Error())
		}
		fmt.Printf("There are %d pods in the cluster\n", len(pods.Items))
		for _, pod := range pods.Items {
			fmt.Println(pod.Name)
		}
	} else if *deployFlag {
		// getoptions := metav1.GetOptions{}
		// clientset.AppsV1().Deployments(namespace).Get(deploymentName, getoptions)
		deploys, err := clientset.AppsV1().Deployments(namespace).List(context.TODO(), metav1.ListOptions{})
		if err != nil {
			if errors.IsNotFound(err) {
				fmt.Printf("not found err=> %v", err.Error())
			} else {
				fmt.Printf("err=> %v", err)
			}
		} else {
			for _, deploy := range deploys.Items {
				fmt.Println(deploy.Name)
			}
		}
	} else if *svcFlag {
		services, err := clientset.CoreV1().Services(namespace).List(context.TODO(), metav1.ListOptions{})
		if err != nil {
			if errors.IsNotFound(err) {
				fmt.Printf("not found err=> %v", err)
			} else {
				fmt.Printf("err=> %v", err)
			}
		} else {
			for _, svc := range services.Items {
				fmt.Println(svc.Name)
			}
		}
	} else if *ingFlag {
		ingresses, err := clientset.ExtensionsV1beta1().Ingresses(namespace).List(context.TODO(), metav1.ListOptions{})
		if err != nil {
			if errors.IsNotFound(err) {
				fmt.Printf("not found err=> %v", err)
			} else {
				fmt.Printf("err=> %v", err)
			}
		} else {
			for _, ing := range ingresses.Items {
				fmt.Println(ing.Name)
			}
		}
	} else if *cmFlag {
		configmaps, err := clientset.CoreV1().ConfigMaps(namespace).List(context.TODO(), metav1.ListOptions{})
		if err != nil {
			if errors.IsNotFound(err) {
				fmt.Printf("not found err=> %v", err)
			} else {
				fmt.Printf("err=> %v", err)
			}
		} else {
			for _, cm := range configmaps.Items {
				fmt.Println(cm.Name)
			}
		}
	}
}
