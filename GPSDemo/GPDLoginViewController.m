//
//  GPDLoginViewController.m
//  GPShopper-iOS
//
//  Created by Matthew Reed on 10/28/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDLoginViewController.h"
#import "GPDRegistrationViewController.h"

@interface GPDLoginViewController ()
{
    SCRegistrationState *state;
    SCProfile *profile;
    SCSession *session;
}



@property (strong, nonatomic) IBOutlet UITextField *usernameTextField;
@property (strong, nonatomic) IBOutlet UITextField *passwordTextField;

@property (strong, nonatomic) IBOutlet UIBarButtonItem *cancelButton;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *spinner;
@property (weak, nonatomic) IBOutlet UIButton *loginButton;

@end

@implementation GPDLoginViewController
@synthesize usernameTextField;
@synthesize passwordTextField;
@synthesize spinner;

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        state = [SCRegistrationState defaultState];
        profile = [SCProfile defaultProfile];
        session = [SCSession defaultSession];
    }
    return self;
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.loginButton.layer.cornerRadius = 2;
    self.navigationItem.leftBarButtonItem = self.cancelButton;
    self.title = @"Login";
    
    [state addObserver:self forKeyPath:@"status" options:0 context:nil];
}

- (void)sessionUpdated {
    if (session.exists) {
        [profile addObserver:self forKeyPath:@"fetchStatus" options:0 context:nil];
        [profile fetch];
    } else if (session.createFailed) {
        
    } else if (session.destroyFailed) {
        
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sessionUpdated) name:@"scsession_updated" object:session];
}

- (void)viewDidDisappear:(BOOL)animated {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"scsession_updated" object:session];
}

- (void)dealloc {
    @try {
        [state removeObserver:self forKeyPath:@"status"];
    }
    @catch (NSException *exception) {
        
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)cancelButtonPressed:(id)sender {
    [state clear];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)loginButtonPressed:(id)sender {
    NSRegularExpression *regex = [[NSRegularExpression alloc] initWithPattern:@"^[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$" options:(NSRegularExpressionCaseInsensitive) error:nil];
    NSTextCheckingResult *match = [regex firstMatchInString:usernameTextField.text options:0 range:NSMakeRange(0, [usernameTextField.text length])];
    
    if  ([usernameTextField.text isEqualToString:@""] || [passwordTextField.text isEqualToString:@""]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"You must enter an email" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else if (!match) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Please enter a valid email." delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else {
        spinner.hidden = NO;
        [state loginWithIdentifier:usernameTextField.text zipcode:@""];
    }
}

- (IBAction)createAccountButtonPressed:(id)sender {
    @try {
        [profile removeObserver:self forKeyPath:@"fetchStatus"];
    }
    @catch (NSException *exception) {
        
    }
    GPDRegistrationViewController *vc = [[GPDRegistrationViewController alloc] initWithNibName:@"GPDRegistrationViewController" bundle:nil];
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    NSLog(@"%@ %@", object, keyPath);
    if ([keyPath isEqualToString:@"status"]) {
        switch (state.status) {
            case SCRegStatusUnregistered:
                
                break;
            case SCRegStatusBusy:
                
                break;
            case SCRegStatusFail:
                
                break;
            case SCRegStatusSuccess:
                [session create];
                break;
        }
    } else if ([keyPath isEqualToString:@"fetchStatus"]) {
        switch (profile.fetchStatus) {
            case SCProfileRemoteBusy:
                
                break;
            case SCProfileRemoteFail:
                
                break;
            case SCProfileRemoteNone:
                
                break;
            case SCProfileRemoteSuccess:
                [[SCShoppingList defaultList] fetch];
                [self dismissViewControllerAnimated:YES completion:nil];
                break;
        }
    }
    
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
